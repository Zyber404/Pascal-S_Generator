// 权值生成模块
#include "ValueGenerator.h"

ValueGenerator::ValueGenerator() {
    // 初始化随机数发生器。这使得每次程序运行时产生的随机数都不同
    srand(time(NULL));
}

std::string ValueGenerator::generateRandomData(int input) {
    int type = input % 4; // 用输入值对4取模来决定生成哪种数据类型
    switch (type) {
    case GEN_INT: // 对应整型 integer
        return std::to_string(rand() % MAX_INT + 1); // 返回一个0到MAX_INT之间的随机整数
    case GEN_CHAR: // 对应实数 char
        return (rand() % 2 == 0) ? std::string(1, 'A' + (rand() % 26)) : std::string(1, 'a' + (rand() % 26)); // 生成A-Z或a-z之间的字符
    case GEN_BOOL: // 对应布尔型 boolean
        return (rand() % 2 == 0) ? "TRUE" : "FALSE"; // 随机返回"true"或"false"
    case GEN_REAL: // 对应字符 real
        return std::to_string((double)(((rand() % 10000) / 10000.1) * MAX_REAL)); // 返回一个0到MAX_REAL之间的随机实数
    default:
        return ""; // 默认情况（实际上不会发生，但为了完整性还是要处理）
    }
}
