#include <iostream>
#include "bankers_algorithm.h"
#include "rag_single_instance.h"

using namespace std;

int main()
{
    cout << "=== Deadlock Detection & Avoidance CLI Tool ===" << endl;
    while (true)
    {
        cout << "\n1. Detect Deadlock (Single Instance using RAG)" << endl;
        cout << "2. Banker's Algorithm (Multiple Instance System)" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            RAGSingleInstance rag;
            int edges;
            cout << "\nEnter number of edges (format: from to): ";
            cin >> edges;
            cout << "\n(Use P1, R1 format. P = Process, R = Resource)" << endl;
            for (int i = 0; i < edges; ++i)
            {
                string from, to;
                cin >> from >> to;
                rag.addEdge(from, to);
            }

            // Print the graph for verification
            rag.printGraph();

            if (rag.detectCycle())
                cout << "\nDeadlock detected via cycle in RAG." << endl;
            else
                cout << "\nNo deadlock detected." << endl;
        }
        else if (choice == 2)
        {
            int p, r;
            cout << "\nEnter number of processes and resources: ";
            cin >> p >> r;
            BankersAlgorithm ba(p, r);
            ba.inputSystemState();

            vector<int> safeSeq;
            if (ba.isSafeState(safeSeq))
            {
                cout << "\nSystem is in a SAFE state. Safe Sequence: ";
                for (int pid : safeSeq)
                    cout << "P" << pid << " ";
                cout << endl;
            }
            else
            {
                cout << "\nSystem is in an UNSAFE state. Deadlock possible." << endl;
            }
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "\nInvalid option. Try again." << endl;
        }
    }
    return 0;
}
