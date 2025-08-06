#ifndef RAG_SINGLE_INSTANCE_H
#define RAG_SINGLE_INSTANCE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>

using namespace std;

class RAGSingleInstance
{
private:
    // adjacency list to store the graph using string node names
    unordered_map<string, vector<string>> adjList;

    // DFS function to check for cycles in the directed graph
    bool dfs(const string &node, unordered_map<string, bool> &visited,
             unordered_map<string, bool> &recStack);

public:
    // Function to add an edge to the graph
    void addEdge(const string &from, const string &to);

    // Function to check if the graph contains a cycle (deadlock detection)
    bool detectCycle();

    // Function to print the graph (for debugging)
    void printGraph();
};

#endif // RAG_SINGLE_INSTANCE_H
