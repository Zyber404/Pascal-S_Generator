#pragma once
// 结构生成模块
#ifndef STRUCTURE_GENERATOR_H
#define STRUCTURE_GENERATOR_H

#include <string>
#include <vector>
#include "ValueGenerator.h"
#include "DeclarationManager.h"
#include <cmath>

#define MIN_CONDITION 3
#define MAX_CONDITION 7 

#define MIN_BASIC_BLOCK 3
#define MAX_BASIC_BLOCK 9 

#define MIN_VAR 10
#define MAX_VAR 30

#define MIN_ASSIGN 5
#define MAX_ASSIGN 15

#define MIN_IF_DEPTH 1
#define MAX_IF_DEPTH 5


#define MIN_FOR_DEPTH 1
#define MAX_FOR_DEPTH 3

#define MIN_LOOP 1
#define MAX_LOOP 3


#define MIN_BLOCK 5
#define MAX_BLOCK 10

#define MIN_PRINT 10
#define MAX_PRINT 30



class StructureGenerator {
private:
    ValueGenerator nameGenerator;
    VariableDeclarationManager Declaration;
public:
    std::string declare(int input, int typeIndex = RANDOM_TYPE);
    std::map<std::string, VariableInfo> arrangement(int input);
    int deleteVar(int input, std::string name);
    std::string assignment(int input);
    std::string basicBlock(int input);
    std::string write(int input);
    // std::string read(int input);
    std::string calculate(int input);
    std::string accumulation(int input);
    std::string absmul(int input);
    std::string sqrt(int input);
    std::string routru(int input);
    std::string odd(int input);
    std::string nestedIfStatement(int input, int depth);
    std::string congeneration(std::map<std::string, VariableInfo> arran);
    void printVariables();
    std::string nestedForLoop(int input, int depth);
    std::string block(int input);
    // 可以添加更多基本结构的生成函数

};

#endif
