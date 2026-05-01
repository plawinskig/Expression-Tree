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
