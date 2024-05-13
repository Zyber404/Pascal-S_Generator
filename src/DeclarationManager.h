#pragma once
// 变量及函数声明模块
#ifndef DECLARATION_MANAGER_H
#define DECLARATION_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include "ValueGenerator.h"
#include <iostream>

#define MAX_NAME_LENGTH 10
#define RANDOM_TYPE 10
#define INT_TYPE 0

class VariableInfo {
public:
    int level;
    std::string name;
    std::string type;
    std::string value; // 变量当前值，根据实际情况进行初始化
};

class VariableDeclarationManager {
private:
    ValueGenerator nameGenerator;
public:
    std::map<std::string, VariableInfo> variables;
    VariableDeclarationManager();
    std::string declareVariable(int input, int typeIndex=RANDOM_TYPE); // 输入参数决定变量级别
    void printVariables(); // 打印所有变量信息
};

#endif