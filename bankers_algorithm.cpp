#include "bankers_algorithm.h"

// Constructor implementation
BankersAlgorithm::BankersAlgorithm(int n, int m) : n(n), m(m)
{
    maxNeed.resize(n, vector<int>(m));
    allocation.resize(n, vector<int>(m));
    need.resize(n, vector<int>(m));
    available.resize(m);
}

void BankersAlgorithm::input()
{
    // get input for maxNeed, allocation and available resources
    cout << "Enter maximum resources needed by each process:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i << ": ";
        for (int j = 0; j < m; j++)
        {
            cin >> maxNeed[i][j];
        }
    }

    cout << "Enter currently allocated resources for each process:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i << ": ";
        for (int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter available resources:\n";
    for (int j = 0; j < m; j++)
    {
        cin >> available[j]; // this is how many of each resource is available actually what we do is that we will subtract the allocated resources from the total resources to get this but here we are assuming that the user will give us the available resources directly
    }

    // Calculate the need matrix(maxNeed - allocation for each process)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }
}

bool BankersAlgorithm::isSafe()
{
    vector<bool> finish(n, false); // to keep track of finished processes
    vector<int> work = available;  // work vector to keep track of available resources
    queue<int> safeSequence;       // to store the safe sequence of processes

    for (int count = 0; count < n; count++)
    {
        // going through n iterations to find a safe sequence
        bool found = false;
        for (int p = 0; p < n; p++)
        {
            // now going through each process
            if (!finish[p])
            {
                // if it hasant been finished yet then we will see if we can allocate resources to it i.e if for each resource type the need of the process is less than or equal to the available resources
                bool canAllocate = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[p][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    // if we can allocate then we will allocate resources to the process and release its allocated resources and add it to the work vector(total available resources)
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[p][j];
                    }
                    finish[p] = true;     // then make it as finished
                    safeSequence.push(p); // then we push it to the safe sequence
                    found = true;
                }
            }
        }
        // if end also we have not found any process that can be allocated resources then we will return false as the system is not in a safe state
        if (!found)
            return false; // No process could be allocated
    }
    // else we will print the safe sequence
    cout << "Safe sequence: ";
    while (!safeSequence.empty())
    {
        cout << safeSequence.front() << " ";
        safeSequence.pop();
    }
    cout << endl;

    return true;
}

// New method to match the interface in main function
void BankersAlgorithm::inputSystemState()
{
    input(); // Delegate to existing input method
}

// New method to check safe state and return safe sequence
bool BankersAlgorithm::isSafeState(vector<int> &safeSequence)
{
    vector<bool> finish(n, false);
    vector<int> work = available;
    safeSequence.clear();

    for (int count = 0; count < n; count++)
    {
        bool found = false;
        for (int p = 0; p < n; p++)
        {
            if (!finish[p])
            {
                bool canAllocate = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[p][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[p][j];
                    }
                    finish[p] = true;
                    safeSequence.push_back(p);
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}