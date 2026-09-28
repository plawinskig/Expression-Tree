# Expression-Tree

This repository contains a Visual Studio solution for working with expression trees, smart pointers, and related logic libraries.

## Projects

- `TepLab3.sln` — main solution file.
- `TepLab3/` — application entry point in `main.cpp`.
- `TepLab3LogicLib/` — logic library for tree and formula handling.
- `TepLab3Tests/` — test project.
- `SmartPointer/` — smart pointer implementation and reference counting example.
- `TepLab4LogicLib/` — additional logic library for result handling.

## Requirements

- Microsoft Visual Studio (2017 or later recommended)
- C++ development workload installed

## Build and Run

1. Open `TepLab3.sln` in Visual Studio.
2. Set the desired startup project:
   - `TepLab3` to run the main application.
   - `TepLab3Tests` to run tests.
3. Build the solution using `Build > Build Solution`.
4. Run the selected project with `Debug > Start Debugging` or `Debug > Start Without Debugging`.

## Build and Run (VS Code / Linux, g++ + CMake)

Requirements: `g++`, `cmake` (3.20+), `gdb`, and the VS Code C/C++ Extension Pack.
googletest is downloaded automatically by CMake on the first configure.

In VS Code:

1. Open the repository folder and pick a GCC kit when CMake Tools asks.
2. Build with `Ctrl+Shift+B` (or the *Build* button in the status bar).
3. Run/debug with `F5` and choose `Debug TepLab3` or `Debug TepLab3Tests`.
4. Run the tests from the Testing panel (CTest), or run `ctest` in `build/`.

From the terminal:

```bash
cmake -S . -B build
cmake --build build -j
(cd TepLab3 && ../build/TepLab3)   # run from TepLab3/ so trees.txt lands there
ctest --test-dir build
```

## Usage

When `TepLab3` runs, the program shows a prompt like `>>>` and accepts the following commands:

- `enter <formula>`
  - Load a new formula into the current tree.
- `get <name>`
  - Load a formula by name or identifier and save it to `TepLab3/trees.txt`.
- `vars`
  - Display the variables currently used in the loaded formula.
- `print`
  - Display the current formula as a string.
- `comp <value1> <value2> ...`
  - Compute the loaded formula using the provided variable values.
- `join <formula>`
  - Join the current formula with another formula.
- `levels`
  - Print the tree levels of the current formula.
- `exit`
  - Exit the application.

Example session:

```text
>>> enter + a * b c
Loaded formula: + a * b c
>>> vars
a b c
>>> comp 1 2 3
7
>>> print
a + b * c
>>> exit
```

## Running Tests

- Open `TepLab3.sln` in Visual Studio.
- Build the solution.
- Use the Test Explorer to discover and run tests from `TepLab3Tests`.

## Notes

- Input files for the main application are available in `TepLab3/`:
  - `trees.txt`
  - `trees_perfect_test.txt`
- The projects use precompiled headers where applicable.

## Contact

For any questions or updates, review the source files and project settings in Visual Studio.
