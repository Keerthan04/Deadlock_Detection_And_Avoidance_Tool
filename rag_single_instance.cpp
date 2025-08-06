#include "rag_single_instance.h"

// Function to add an edge to the graph
void RAGSingleInstance::addEdge(const string &from, const string &to)
{
    adjList[from].push_back(to);
    // Ensure both nodes exist in the adjacency list
    if (adjList.find(to) == adjList.end())
    {
        adjList[to] = vector<string>();
    }
}

// DFS function to check for cycles in the directed graph
bool RAGSingleInstance::dfs(const string &node, unordered_map<string, bool> &visited,
                            unordered_map<string, bool> &recStack)
{
    visited[node] = true;
    recStack[node] = true;

    for (const string &neighbor : adjList[node])
    {
        if (!visited[neighbor])
        {
            if (dfs(neighbor, visited, recStack))
            {
                return true;
            }
        }
        else if (recStack[neighbor])
        {
            return true; // Back edge found, cycle detected
        }
    }

    recStack[node] = false;
    return false;
}

// Function to check if the graph contains a cycle (deadlock detection)
bool RAGSingleInstance::detectCycle()
{
    unordered_map<string, bool> visited;
    unordered_map<string, bool> recStack;

    // Initialize visited and recursion stack
    for (const auto &pair : adjList)
    {
        visited[pair.first] = false;
        recStack[pair.first] = false;
    }

    // Check for cycle in different DFS trees
    for (const auto &pair : adjList)
    {
        if (!visited[pair.first])
        {
            if (dfs(pair.first, visited, recStack))
            {
                return true;
            }
        }
    }
    return false;
}

// Function to print the graph (for debugging)
void RAGSingleInstance::printGraph()
{
    cout << "\nResource Allocation Graph:" << endl;
    for (const auto &pair : adjList)
    {
        cout << pair.first << " -> ";
        for (size_t i = 0; i < pair.second.size(); i++)
        {
            cout << pair.second[i];
            if (i < pair.second.size() - 1)
                cout << ", ";
        }
        cout << endl;
    }
}