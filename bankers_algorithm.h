#ifndef BANKERS_ALGORITHM_H
#define BANKERS_ALGORITHM_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

class BankersAlgorithm
{
private:
    int n, m;                                      // n = number of processes and m = number of resources
    vector<vector<int>> maxNeed, allocation, need; // for each process m resources we will have max needed for that process, currently allocated resources and remaining resources needed
    vector<int> available;                         // available resources - this of length m which will tell us the total available resources of each type

public:
    // Constructor
    BankersAlgorithm(int n, int m);

    // Method to get input for the algorithm
    void inputSystemState();

    // Method to check if the system is in a safe state and return safe sequence
    bool isSafeState(vector<int> &safeSequence);

    // Legacy method for backward compatibility
    void input();
    bool isSafe();
};

#endif // BANKERS_ALGORITHM_H
