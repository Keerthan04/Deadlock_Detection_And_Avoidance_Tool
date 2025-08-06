@echo off
echo Compiling Deadlock Detection & Avoidance Tool...
g++ -std=c++11 -Wall -Wextra -o deadlock_tool.exe main.cpp bankers_algorithm.cpp rag_single_instance.cpp
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful! Run deadlock_tool.exe to execute.
) else (
    echo Compilation failed!
)
pause
