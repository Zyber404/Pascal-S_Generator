// 变量及函数声明模块
#include "DeclarationManager.h"
#include <iostream>
#include <cstdlib> // For rand and srand
#include <ctime> // For time

VariableDeclarationManager::VariableDeclarationManager()
{
}

std::string VariableDeclarationManager::declareVariable(int input, int typeIndex) {
    std::string name; // 生成随机变量名
    int name_length = rand() % (MAX_NAME_LENGTH + 1);

    name += nameGenerator.generateRandomData(GEN_CHAR);
    name += nameGenerator.generateRandomData(GEN_INT);
    for (int i = 1; i <= name_length + 1; i++)
        name += nameGenerator.generateRandomData(GEN_CHAR);

    //lower name
    for (int i = 0; i < name.length(); i++) {
        if (name[i] >= 'A' && name[i] <= 'Z') {
            name[i] = name[i] + 32;
        }
    }

    // 变量名查重
    while (variables.find(name) != variables.end()) // 如果变量名已存在
    {
        name = "";
        for (int i = 1; i <= name_length + 1; i++)
            name += nameGenerator.generateRandomData(GEN_CHAR);
    }
    if (typeIndex == RANDOM_TYPE) {
        typeIndex = rand() % 4;
    }
    std::string type;
    std::string initValue;
    switch (typeIndex) {
    case 0: 
        type = "integer";
        initValue = nameGenerator.generateRandomData(GEN_INT);
        break;
    case 1: 
        type = "boolean";
        initValue = nameGenerator.generateRandomData(GEN_BOOL);
        break;
    case 2: 
        type = "char";
        initValue = "'" + nameGenerator.generateRandomData(GEN_CHAR) + "'";
        break;
    case 3: 
        type = "real";
        initValue = nameGenerator.generateRandomData(GEN_REAL);
        break;
    default: type = "integer"; // 默认为int类型
    }

    // // 默认值设定，实际应用中可能会根据类型不同而不同
    // std::string defaultValue = (type == "int" || type == "real") ? "0" :
    //     (type == "boolean" ? "FALSE" : "' '");

    // 将变量信息存入表中
    variables[name] = { input, name, type, initValue };
    return name;
}

//打印变量表
void VariableDeclarationManager::printVariables() {
    for (const auto& varPair : variables) {
        const VariableInfo& var = varPair.second;
        std::cout << "Level: " << var.level << ", Name: " << var.name
            << ", Type: " << var.type << ", Value: " << var.value << std::endl;
    }
}

std::string getRandomType(std::vector<VariableInfo> params)
{
    return params[rand() % params.size()].type;
}
