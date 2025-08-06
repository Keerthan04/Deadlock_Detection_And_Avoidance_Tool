# 🔐 Deadlock Detection & Avoidance Tool (CLI-based)

A command-line based simulator for detecting and avoiding deadlocks in operating systems using:

- **Cycle Detection in Resource Allocation Graph (RAG)** — for single-instance resources
- **Banker's Algorithm** — for multiple-instance resources

## 📺 Demo Video

## 📺 Demo Video

[![Watch on YouTube](https://img.youtube.com/vi/_hDNrIBgzTQ/0.jpg)](https://www.youtube.com/watch?v=_hDNrIBgzTQ)


## 🧠 Why This Project?

Deadlocks are a critical problem in concurrent systems, especially in OS, database systems, and distributed systems. This tool provides hands-on simulation of how deadlocks can occur and how they can be detected or avoided in real-time.

✅ Useful for learning OS concepts  
✅ Ideal for academic demos and placement discussions  
✅ Implements two major strategies based on real-world OS handling techniques

## 📌 Features

### 🔁 1. Resource Allocation Graph (RAG) – Single Instance Resources

- **Nodes**: Processes (P) and Resources (R)
- **Edges**: Allocation (R → P) and Request (P → R)
- **Detection**: Uses DFS cycle detection – if a cycle is found, it indicates a deadlock

#### ✅ Sample Input:

```bash
Enter number of edges: 4
P1 R1
R1 P2
P2 R2
R2 P1
```

#### 🛑 Output:

```bash
Deadlock Detected: Cycle → P1 → R1 → P2 → R2 → P1
```

### 💡 2. Banker's Algorithm – Multiple Instance Resources

- Checks system safety by simulating resource allocation
- Avoids entering an unsafe state by checking if all processes can finish
- Implements:
  - Need matrix = Max - Allocated
  - Safety sequence detection loop

#### ✅ Sample Input:

```bash
Number of processes: 3
Number of resources: 3

Maximum resources needed:
P0: 7 5 3
P1: 3 2 2
P2: 9 0 2

Currently allocated:
P0: 0 1 0
P1: 2 0 0
P2: 3 0 2

Available resources: 3 3 2
```

#### 🔄 Output:
```
System is in a SAFE state. Safe sequence: P1 P0 P2
```

## 🛠️ How It Works

### 🗂️ Project Structure
```
/Deadlock_Simulator
│
├── main.cpp                    # Entry point with CLI menu
├── rag_single_instance.cpp     # RAG logic and cycle detection (DFS)
├── rag_single_instance.h       # RAG header file
├── bankers_algorithm.cpp       # Banker's algorithm implementation
├── bankers_algorithm.h         # Banker's algorithm header file
├── deadlock_simulator.cpp      # Additional deadlock simulation
├── Makefile                    # For Linux/Mac compilation
├── compile.bat                 # For Windows compilation
├── README.md                   # This file
└── .gitignore                  # Git ignore file
```

### 🧵 Key Algorithms Implemented

#### Resource Allocation Graph (RAG)
- Uses adjacency list representation with string-based node names
- Implements DFS with recursion stack for cycle detection
- Supports dynamic edge addition for real-time testing

#### Banker's Algorithm
- Maintains allocation, maximum need, and need matrices
- Implements safety algorithm to find safe execution sequence
- Provides both legacy and modern interfaces for compatibility

## 🚀 Compilation Instructions

### Windows
```bash
# Using batch file
compile.bat

# Or manually
g++ -std=c++11 -Wall -Wextra -o deadlock_tool.exe main.cpp bankers_algorithm.cpp rag_single_instance.cpp
```

### Linux / Mac
```bash
# Using Makefile
make

# Or manually
g++ -std=c++11 -Wall -Wextra -o deadlock_tool main.cpp bankers_algorithm.cpp rag_single_instance.cpp
```

## 🧪 How to Run

After compiling, run the executable:

```bash
./deadlock_tool      # Linux/Mac
deadlock_tool.exe    # Windows
```

### Menu Options:
```
=== Deadlock Detection & Avoidance CLI Tool ===

1. Detect Deadlock (Single Instance using RAG)
2. Banker's Algorithm (Multiple Instance System)
3. Exit
```

## 📋 Usage Examples

### Example 1: RAG Deadlock Detection
```
Choose option: 1
Enter number of edges: 4
(Use P1, R1 format. P = Process, R = Resource)
P1 R1
R1 P2
P2 R2
R2 P1

Resource Allocation Graph:
P1 -> R1
R1 -> P2
P2 -> R2
R2 -> P1

Deadlock detected via cycle in RAG.
```

### Example 2: Banker's Algorithm (Safe State)
```
Choose option: 2
Enter number of processes and resources: 3 3

Enter maximum resources needed by each process:
Process 0: 7 5 3
Process 1: 3 2 2
Process 2: 9 0 2

Enter currently allocated resources for each process:
Process 0: 0 1 0
Process 1: 2 0 0
Process 2: 3 0 2

Enter available resources: 3 3 2

System is in a SAFE state. Safe Sequence: P1 P0 P2
```

## 🔧 Technical Details

### Dependencies
- **C++ Standard**: C++11 or later
- **Compiler**: GCC/Clang/MSVC with C++11 support
- **Libraries**: Standard Template Library (STL)

### Key Classes

#### `RAGSingleInstance`
```cpp
class RAGSingleInstance {
private:
    unordered_map<string, vector<string>> adjList;
    bool dfs(const string& node, unordered_map<string, bool>& visited, 
             unordered_map<string, bool>& recStack);
public:
    void addEdge(const string& from, const string& to);
    bool detectCycle();
    void printGraph();
};
```

#### `BankersAlgorithm`
```cpp
class BankersAlgorithm {
private:
    int n, m;
    vector<vector<int>> maxNeed, allocation, need;
    vector<int> available;
public:
    BankersAlgorithm(int n, int m);
    void inputSystemState();
    bool isSafeState(vector<int>& safeSequence);
};
```

## 🧱 Future Enhancements

- [ ] **GUI/Visualization**: Add graphical interface using Qt or web-based visualization
- [ ] **Process Simulation**: Use `std::thread` to show dynamic locking scenarios
- [ ] **Graph Export**: Export RAG to Graphviz format for visualization
- [ ] **Unit Tests**: Comprehensive test suite for edge cases
- [ ] **Performance Metrics**: Add timing and memory usage analysis
- [ ] **Configuration Files**: Support for loading test cases from JSON/XML
- [ ] **Network Simulation**: Extend to distributed deadlock detection

## 🎯 Learning Objectives

This project helps understand:
- **Deadlock conditions**: Mutual exclusion, hold and wait, no preemption, circular wait
- **Detection algorithms**: Graph-based cycle detection
- **Avoidance strategies**: Resource allocation algorithms
- **System state analysis**: Safe vs unsafe states
- **Data structures**: Adjacency lists, matrices, graph traversal
- **C++ concepts**: Classes, STL containers, file organization

## 🧾 Credits

**Built with ❤️ by Keerthan Kumar C** to explore OS internals through simulation.

Inspired by classic Operating System textbooks and academic OS labs.

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

### 📞 Contact

For questions, suggestions, or contributions, feel free to reach out!

**Happy Learning! 🚀**
