// deadlock_simulator_with_cycle.cpp
// Compile:
//   Linux/Mac: g++ -std=c++11 -Wall -Wextra -o deadlock_simulator_with_cycle deadlock_simulator_with_cycle.cpp
//   Windows (MSYS/MinGW): g++ -std=c++11 -Wall -Wextra -o deadlock_simulator_with_cycle.exe deadlock_simulator_with_cycle.cpp
//
// Requirements:
//   Graphviz installed (dot command available in PATH)
//   Run the program and it will generate rag.png after each update.

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <functional>

using namespace std;

// -------------------- GLOBAL DATA --------------------
unordered_map<string, vector<string>> adjList; // Resource Allocation Graph (directed)
mutex graphMutex; // Protects adjList

// -------------------- DFS Cycle Detection (Single-Instance RAG) --------------------
// Returns a vector representing the cycle nodes in order, or empty vector if no cycle.
vector<string> detectCycleLocked() {
    // caller must hold graphMutex OR we can lock here for safety
    unordered_map<string, bool> visited;
    unordered_map<string, bool> recStack;
    unordered_map<string, string> parent; // to reconstruct cycle

    function<vector<string>(const string&)> dfs = [&](const string& node) -> vector<string> {
        visited[node] = true;
        recStack[node] = true;

        for (const string &neigh : adjList[node]) {
            if (!visited[neigh]) {
                parent[neigh] = node;
                vector<string> res = dfs(neigh);
                if (!res.empty()) return res; // propagate cycle upward
            } else if (recStack[neigh]) {
                // Found cycle: reconstruct path from node -> neigh
                vector<string> cycle;
                string cur = node;
                cycle.push_back(neigh); // start with entry point
                while (cur != neigh && !cur.empty()) {
                    cycle.push_back(cur);
                    cur = parent.count(cur) ? parent[cur] : string();
                }
                cycle.push_back(neigh); // close the cycle
                reverse(cycle.begin(), cycle.end());
                return cycle;
            }
        }

        recStack[node] = false;
        return {};
    };

    // Ensure we iterate over all nodes (processes and resources)
    for (const auto &kv : adjList) {
        const string &node = kv.first;
        if (!visited[node]) {
            // ensure parent[node] exists as empty to avoid uninitialized lookups
            parent[node] = string();
            vector<string> res = dfs(node);
            if (!res.empty()) return res;
        }
    }
    return {};
}

// Thread-safe wrapper that locks the graph and returns cycle (or empty)
vector<string> detectCycle() {
    lock_guard<mutex> lock(graphMutex);
    return detectCycleLocked();
}

// -------------------- RAG Export (Graphviz) with highlighting --------------------
void exportRAGToDot(const unordered_map<string, vector<string>>& graph,
                    const unordered_set<string>& highlightNodes,
                    const string& filename) {
    ofstream file(filename);
    file << "digraph RAG {\n";
    file << "  rankdir=LR;\n";
    file << "  node [shape=ellipse, fontsize=12, style=filled, fillcolor=white];\n";

    // Print nodes (collect unique nodes)
    unordered_set<string> nodes;
    for (auto &kv : graph) {
        nodes.insert(kv.first);
        for (auto &v : kv.second) nodes.insert(v);
    }

    for (const string &n : nodes) {
        if (highlightNodes.count(n)) {
            file << "  \"" << n << "\" [fillcolor=\"/pastel13/1\", color=red, fontcolor=black, penwidth=2];\n";
        } else {
            file << "  \"" << n << "\";\n";
        }
    }

    // Print edges
    for (auto& [node, neighbors] : graph) {
        for (const string &neighbor : neighbors) {
            file << "  \"" << node << "\" -> \"" << neighbor << "\";\n";
        }
    }

    file << "}\n";
    file.close();
}

void generateGraphImageAndOpen(const unordered_set<string>& highlightNodes) {
    // copy graph under lock
    unordered_map<string, vector<string>> copyGraph;
    {
        lock_guard<mutex> lock(graphMutex);
        copyGraph = adjList;
    }

    exportRAGToDot(copyGraph, highlightNodes, "rag.dot");
    // Generate image (blocking)
    int rc = system("dot -Tpng rag.dot -o rag.png");
    if (rc != 0) {
        cerr << "Warning: Graphviz 'dot' failed (rc=" << rc << "). Make sure Graphviz is installed.\n";
        return;
    }

    // Open the image using OS default viewer
#ifdef _WIN32
    system("start rag.png");
#elif __APPLE__
    system("open rag.png");
#else
    system("xdg-open rag.png &>/dev/null");
#endif
}

// -------------------- Process Simulation --------------------
void addEdgeLocked(const string& from, const string& to) {
    // Assumes graphMutex held by caller or use lock_guard inside for extra safety
    adjList[from].push_back(to);
}

void removeEdgeLocked(const string& from, const string& to) {
    auto it = adjList.find(from);
    if (it != adjList.end()) {
        auto &vec = it->second;
        vec.erase(remove(vec.begin(), vec.end(), to), vec.end());
    }
}

void processFunction(int processId, vector<string> resources) {
    string pName = "P" + to_string(processId);

    for (auto &res : resources) {
        // Request resource (P -> R)
        {
            lock_guard<mutex> lock(graphMutex);
            addEdgeLocked(pName, res);
            cout << "[Request] " << pName << " -> " << res << endl;
        }

        // Detect cycle and visualize
        vector<string> cycle = detectCycle();
        unordered_set<string> highlight;
        if (!cycle.empty()) {
            cout << "⚠ Deadlock detected! Cycle: ";
            for (size_t i = 0; i < cycle.size(); ++i) {
                cout << cycle[i] << (i + 1 < cycle.size() ? " -> " : "");
                highlight.insert(cycle[i]);
            }
            cout << "\n";
        }

        // Generate graph (with highlighted cycle nodes if any)
        generateGraphImageAndOpen(highlight);

        // Simulate some work while holding the resource
        this_thread::sleep_for(chrono::milliseconds(rand() % 1200 + 400));

        // Release resource (remove P -> R)
        {
            lock_guard<mutex> lock(graphMutex);
            removeEdgeLocked(pName, res);
            cout << "[Release] " << pName << " -/-> " << res << endl;
        }

        // After release, visualize again
        vector<string> cycleAfterRelease = detectCycle();
        unordered_set<string> highlightAfter;
        if (!cycleAfterRelease.empty()) {
            for (auto &n : cycleAfterRelease) highlightAfter.insert(n);
        }
        generateGraphImageAndOpen(highlightAfter);

        // Small pause between actions so image viewer has time to open (optional)
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

// -------------------- MAIN --------------------
int main() {
    srand((unsigned)time(nullptr));
    cout << "Deadlock Simulator (multithreaded) with cycle visualization\n";

    // Example scenario that can cause a cycle:
    // P0 requests R1 then R2
    // P1 requests R2 then R3
    // P2 requests R3 then R1  -> cycle across R1,R2,R3 and P0,P1,P2 can form

    vector<vector<string>> processResources = {
        {"R1", "R2"},
        {"R2", "R3"},
        {"R3", "R1"}
    };

    vector<thread> processes;
    for (int i = 0; i < (int)processResources.size(); i++) {
        processes.emplace_back(processFunction, i, processResources[i]);
        // stagger thread starts slightly for clearer visualization
        this_thread::sleep_for(chrono::milliseconds(250));
    }

    for (auto &t : processes) {
        if (t.joinable()) t.join();
    }

    cout << "Simulation completed.\n";
    return 0;
}
