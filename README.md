# PASCAL-S generator & test script
[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FZyber404%2FPascal-S_Generator&count_bg=%2379C83D&title_bg=%23555555&icon=awesomelists.svg&icon_color=%23E7E7E7&title=visitors&edge_flat=false)](https://hits.seeyoufarm.com)
## Introduction
- This project based on BUPT SCS *Compilation Principles and Techniques Course Design*.

- This is a simple project to generate Pascal-S code, and if you have a Pascal-S to C compiler, this are two Python scripts to compile and compare the result between the generated Pascal-S code and  compiled C code.

- If this project helps you, please give me a ⭐, which will be a great encouragement to me!

## Features
1. Support assignment, baisc calculation, nested if-else, nested for, function call ( Only functions with depth ***1*** are supported, just like C ) and std-out statement.
2. Try our best to avoid the division by zero fault, but it is still possible. This fault will make lines behind the fault line not executed and you will see nothing is printed. It will **NOT** effect the correctness of the generated code, it just make the code *meaningless*.
3.  Nested if-else, nested for and function call can be **nested within each other**, which increase the complexity of the generated code.
4. The length of the generated code is about 1000 lines, but you can chanege macros in the `src/StructureGenerator.h` to customize the length of your generated code.

## How to use
### 1. Prepare
You need to install fpc, CMake and Python with following command.
```bash
sudo apt-get install fpc
sudo apt-get install cmake
sudo apt-get install python3
```
### 2. Build
You can build the project with following command.
```bash
mkdir -p ./build
cd ./build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug --target all -j 26
```
### 3. Quick Start
There is already a Pascal-S to C compiler in `compiler/`. After build with CMake, you just need to run the python script.
```bash
python compile_compare.py
```
You can also check consistency of output of the generated Pascal-S code and compiled C code with following command.
```bash
python statistic.py
```
