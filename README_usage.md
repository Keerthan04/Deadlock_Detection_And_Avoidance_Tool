# Deadlock Detection & Avoidance Tool

This project implements two key deadlock detection and avoidance algorithms:

## 1. Resource Allocation Graph (RAG) - Single Instance

For systems with single instance resources, deadlock detection using cycle detection in RAG.

### Example Input for RAG:

```
Enter number of edges: 4
P1 R1
R1 P2
P2 R2
R2 P1
```

This creates a cycle: P1 → R1 → P2 → R2 → P1 (Deadlock detected)

## 2. Banker's Algorithm - Multiple Instance

For systems with multiple instances of resources, using Banker's algorithm for deadlock avoidance.

### Example Input for Banker's Algorithm:

```
Number of processes: 3
Number of resources: 3

Maximum resources needed:
Process 0: 7 5 3
Process 1: 3 2 2
Process 2: 9 0 2

Currently allocated:
Process 0: 0 1 0
Process 1: 2 0 0
Process 2: 3 0 2

Available resources: 3 3 2
```

## Compilation:


- Windows: Run `compile.bat`
- Linux/Mac: Run `make`

## Usage:

Just run ./deadlock_tool.exe
or `./deadlock_tool` after compilation. The program will prompt you to choose between the RAG or Banker's algorithm.
Run the executable and choose from the menu options to test different deadlock scenarios.
