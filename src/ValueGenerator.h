#pragma once
// 权值生成模块
#ifndef VALUE_GENERATOR_H
#define VALUE_GENERATOR_H

#include <string>
#include <stdlib.h> // 引入标准库支持随机数生成
#include <time.h>   // 引入时间库用于随机数种子
#define GEN_INT 0
#define GEN_CHAR 1
#define GEN_BOOL 2
#define GEN_REAL 3

#define MAX_INT 100
#define MAX_REAL 100.0

class ValueGenerator {
public:
    ValueGenerator();                     // 构造函数
    std::string generateRandomData(int input); // 根据输入生成随机数据的函数
};

#endif
