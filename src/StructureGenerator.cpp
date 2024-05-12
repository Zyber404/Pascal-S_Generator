// 模块生成函数
#include "StructureGenerator.h"
#include <cstdlib>
#include <ctime>

// 声明变量
std::string StructureGenerator::declare(int input) {
    std::string name = Declaration.declareVariable(input);
    return Declaration.variables[name].name + ":" + Declaration.variables[name].type + ";\n";
}

// 获得给定作用域的变量
std::map<std::string, VariableInfo> StructureGenerator::arrangement(int input) {  
    std::map<std::string, VariableInfo> arran;
    for (const auto& item : Declaration.variables) {
        if (item.second.level == input) {
            arran.emplace(item);
        }

    }
    return arran;
}

// 赋值
std::string StructureGenerator::assignment(int input) {
    std::map<std::string, VariableInfo> arran = arrangement(input);
    int randIndex = rand() % arran.size(); // 生成随机索引
    auto it = arran.begin(); // 获取map的开始迭代器
    std::advance(it, randIndex); // 将迭代器移动到随机选中的项

    std::string name = it->second.name;
    if (Declaration.variables[name].type == "integer") {
        Declaration.variables[name].value = nameGenerator.generateRandomData(GEN_INT);
    }
    else if (Declaration.variables[name].type == "char") {
        Declaration.variables[name].value = "'" + nameGenerator.generateRandomData(GEN_CHAR) + "'";
    }
    else if (Declaration.variables[name].type == "boolean") {
        Declaration.variables[name].value = nameGenerator.generateRandomData(GEN_BOOL);
    }
    else if (Declaration.variables[name].type == "real") {
        Declaration.variables[name].value = nameGenerator.generateRandomData(GEN_REAL);
    }
    else {
        std::cout << "assign error: type not found" << std::endl;
    }
    return Declaration.variables[name].name + " := " + Declaration.variables[name].value + ";\n";
}


// write
std::string StructureGenerator::write(int input) {
    std::map<std::string, VariableInfo> arran = arrangement(input);
    int tim = rand();
    std::string content;
    if (tim % 10 == 0 || arran.empty()) { // 10%概率打印随机字符串
        content += "'";
        for (int i = 1; i <= tim % 10 + 1; i++) {
            int tim2 = rand() % 2;
            content += nameGenerator.generateRandomData(tim2);
        }
        content += "'";
    }
    else {
        int randIndex = rand() % arran.size(); // 生成随机索引
        auto it = arran.begin(); // 获取map的开始迭代器
        std::advance(it, randIndex); // 将迭代器移动到随机选中的项
        content += it->second.name;
    }
    // if (tim % 2 == 0) {
    //     return "write (" + content + ");\n";
    // }
    // else {
        return "writeln (" + content + ");\n";
    // }
}

// read
// std::string StructureGenerator::read(int input) {
//     std::map<std::string, VariableInfo> arran = arrangement(input);
//     if (arran.empty()) {
//         std::cout << "The map is empty." << std::endl;
//         return " ";
//     }
//
//     int count = 0;
//     for (const auto& item : arran) {
//         if (item.second.type != "boolean") {
//             ++count;
//         }
//     }
//     if (count == 0) {
//         std::cout << "error";
//         return " ";
//     }
//     int num = rand() % count + 1;
//     auto it = arran.begin();
//
//     while (num > 0) {
//         // 如果当前项不是boolean类型，num减一
//         if (it->second.type != "boolean") {
//             --num;
//
//             // 如果num变为0，打印当前项信息
//             if (num == 0) {
//                 return "read (" + it->second.name + ");\n";
//             }
//         }
//         ++it;
//     }
//     return " ";
// }

//+-*/mod
std::string StructureGenerator::calculate(int input) {
    VariableInfo par[3];
    std::map<std::string, VariableInfo> arran = arrangement(input);
    if (arran.empty()) {
        std::cout << "The map is empty." << std::endl;
        return " ";
    }
    int count = 0;
    for (const auto& item : arran) {
        if (item.second.type == "integer" || item.second.type == "real") {
            ++count;
        }
    }
    if (count == 0) {
        std::cout << "calc error: no int or real var" << std::endl;
        return " ";
    }
    //找三个int或real类型的变量
    for (int i = 0; i < 3; i++) {
        //  找第num个int或real类型的变量
        int num = rand() % count + 1;
        auto it = arran.begin();
        while (num > 0) {
            if (it->second.type == "integer" || it->second.type == "real") {
                --num;
                // 找到了第num个int或real类型的变量
                if (num == 0) {
                    par[i] = it->second;
                }
            }
            ++it;
        }
    }

    if(par[0].type == "integer" && par[1].type == "real") {
        VariableInfo temp = par[0];
        par[0] = par[1];
        par[1] = temp;
    }

    if(par[0].type == "integer" && par[2].type == "real") {
        VariableInfo temp = par[0];
        par[0] = par[2];
        par[2] = temp;
    }


    int int0, int1, int2;
    double real0, real1, real2;
    int randm = rand() % 2;
    int1 = std::stoi(par[1].value);
    real1 = std::stod(par[1].value);
    if (randm == 0) {
        int2 = std::stoi(par[2].value);
        real2 = std::stod(par[2].value);
    }
    else {
        int2 = std::stoi(nameGenerator.generateRandomData(GEN_INT));
        real2 = std::stod(nameGenerator.generateRandomData(GEN_REAL));
    }

    // while ((((cal == 12 && int2 == 0) || (cal == 13 && int1 == 0) || (cal == 16 && int2 == 0) || (cal == 17 && int1 == 0)) && par[1].type == "integer") || ((cal == 12 && int2 == 0) || (cal == 13 && real1 == 0) || (cal == 14 && real2 == 0) || (cal == 15 && real1 == 0) || (cal == 16 && int2 == 0) || (cal == 17 && real1 == 0) || (cal == 18 && real2 == 0) || (cal == 19 && real1 == 0)) ) {
    //     cal = rand() % 20;
    // }
    int cal = rand() % 5;
    // 只有两个变量都是int时，左值才为int，否则为real
    if (par[1].type == "integer" && par[2].type == "integer") {
        while((cal == 3 && int2 == 0) || (cal == 4 && int2 == 0)) {
            cal = rand() % 5;
        }
        switch (cal) {
        case 0: int0 = int1 + int2; break;
        case 1: int0 = int1 - int2; break;
        case 2: int0 = int1 * int2; break;
        case 3: int0 = int1 / int2; break;
        case 4: int0 = int1 % int2; break;
        }
        par[0].value = std::to_string(int0);
        // par[0].type = "integer";
    }
    else {
        while((cal == 3 && real2 == 0 || cal == 4)) {
            cal = rand() % 4;

        }
        switch (cal) {
        case 0: real0 = real1 + real2; break;
        case 1: real0 = real1 - real2; break;
        case 2: real0 = real1 * real2; break;
        case 3: real0 = real1 / real2; break;
        }
        par[0].value = std::to_string(real0);
        // par[0].type = "real";
    }
    // Declaration.variables[par[0].name].type = par[0].type;
    // Declaration.variables[par[0].name].value = par[0].value;

    std::string result;
    std::string name2;
    if (randm == 0) {
        name2 = par[2].name;
    }
    else {
        if (par[2].type == "integer") {
            name2 = std::to_string(int2);
        }
        else {
            name2 = std::to_string(real2);
        }
    }
    switch (cal) {
    case 0: result = par[0].name + " := " + par[1].name + " + " + name2 + ";\n"; break;
    case 1: result = par[0].name + " := " + par[1].name + " - " + name2 + ";\n"; break;
    case 2: result = par[0].name + " := " + par[1].name + " * " + name2 + ";\n"; break;
    case 3: {
        if ( par[1].type == "integer" && par[2].type == "integer") {
            result = par[0].name + " := " + par[1].name + " div " + name2 + ";\n";
        }
        else {
            result = par[0].name + " := " + par[1].name + " / " + name2 + ";\n";
        }
        break;}
    case 4: result = par[0].name + " := " + par[1].name + " mod " + name2 + ";\n"; break;
    }
    return result;
}

// 累加（减）
std::string StructureGenerator::accumulation(int input){
    VariableInfo par[2];
    std::map<std::string, VariableInfo> arran = arrangement(input);
    if (arran.empty()) {
        std::cout << "The map is empty." << std::endl;
        return " ";
    }
    int count = 0;
    for (const auto& item : arran) {
        if (item.second.type == "integer") {
            ++count;
        }
    }
    if (count == 0) {
        std::cout << "error";
        return " ";
    }

    for (int i = 0; i < 2; i++) {
        //  循环两次
        int num = rand() % count + 1;
        auto it = arran.begin();
        while (num > 0) {
            // 如果当前项为int类型，num减一
            if (it->second.type == "integer") {
                --num;

                // 如果num变为0，读取
                if (num == 0) {
                    par[i] = it->second;
                }
            }
            ++it;
        }
    }

    int acc = rand() % 10;
    int var1, var2;
    var1 = std::stoi(par[0].value);
    var2 = std::stoi(par[1].value);
    if (acc % 2 == 0) {  // +
        if (acc == 0) {
            Declaration.variables[par[0].name].value = std::to_string(var1 + var2);
            return "Inc(" + par[0].name + ", " + par[1].name + ");\n";
        }
        else {
            Declaration.variables[par[0].name].value = std::to_string(var1 + 1);
            return "Inc(" + par[0].name + ");\n";
        }
    }
    else {  // -
        if (acc == 1) {
            Declaration.variables[par[0].name].value = std::to_string(var1 - var2);
            return "Dec(" + par[0].name + ", " + par[1].name + ");\n";
        }
        else {
            Declaration.variables[par[0].name].value = std::to_string(var1 - 1);
            return "Dec(" + par[0].name + ");\n";
        }
    }

}

// 绝对值、自乘
std::string StructureGenerator::absmul(int input) {
    VariableInfo par[2];
    std::map<std::string, VariableInfo> arran = arrangement(input);
    if (arran.empty()) {
        std::cout << "The map is empty." << std::endl;
        return " ";
    }
    int countint = 0;
    int countreal = 0;
    for (const auto& item : arran) {
        if (item.second.type == "integer") {
            ++countint;
        }
        else if (item.second.type == "real") {
            ++countreal;
        }
    }
    int count = countint + countreal;
    if (count == 0) {
        std::cout << "can't absmul";
        return " ";
    }

    int num = rand() % count + 1;
    auto it = arran.begin();
    while (num > 0) {
        // 如果当前项为int或real类型，num减一
        if (it->second.type == "integer" || it->second.type == "real") {
            --num;

            // 如果num变为0，读取
            if (num == 0) {
                par[0] = it->second;
            }
        }
        ++it;
    }
    int countsel = 0;
    if (par[0].type == "integer") {
        countsel = countint;
    }
    else {
        countsel = countreal;
    }
    num = rand() % countsel + 1;
    it = arran.begin();
    while (num > 0) {
        // 如果当前项为int或real类型，num减一
        if (it->second.type == par[0].type) {
            --num;

            // 如果num变为0，读取
            if (num == 0) {
                par[1] = it->second;
            }
        }
        ++it;
    }

    int jud = rand() % 2;
    if (jud == 0) { //绝对值
        if (par[0].type == "integer") {
            int var = std::stoi(par[1].value);
            Declaration.variables[par[0].name].value = std::to_string(abs(var));
        }
        else {
            double var = std::stod(par[1].value);
            Declaration.variables[par[0].name].value = std::to_string(fabs(var));
        }
        return par[0].name + " := Abs(" + par[1].name + ");\n";
    }
    else {  //自乘
        if (par[0].type == "integer") {
            int var = std::stoi(par[1].value);
            Declaration.variables[par[0].name].value = std::to_string(var * var);
        }
        else {
            double var = std::stod(par[1].value);
            Declaration.variables[par[0].name].value = std::to_string(var * var);
        }
        return par[0].name + " := Sqr(" + par[1].name + ");\n";
    }

}

// 平方根
std::string StructureGenerator::sqrt(int input) {
    VariableInfo par[2];
    std::map<std::string, VariableInfo> arran = arrangement(input);
    if (arran.empty()) {
        std::cout << "The map is empty." << std::endl;
        return " ";
    }
    int count = 0;
    for (const auto& item : arran) {
        if (item.second.type == "real") {
            ++count;
        }
    }
    if (count == 0) {
        std::cout << "error";
        return " ";
    }

    for (int i = 0; i < 2; i++) {
        //  循环两次
        int num = rand() % count + 1;
        auto it = arran.begin();
        while (num > 0) {
            // 如果当前项为int类型，num减一
            if (it->second.type == "real") {
                --num;

                // 如果num变为0，读取
                if (num == 0) {
                    par[i] = it->second;
                }
            }
            ++it;
        }
    }

    double var = std::stod(par[1].value);
    Declaration.variables[par[0].name].value = std::to_string(std::sqrt(var));
    
    return par[0].name + " := Sqrt(" + par[1].name + ");\n";
}

// 近似值
std::string StructureGenerator::routru(int input) {
    VariableInfo par[2];
    std::map<std::string, VariableInfo> arran = arrangement(input);
    if (arran.empty()) {
        std::cout << "The map is empty." << std::endl;
        return " ";
    }
    int countint = 0;
    int countreal = 0;
    for (const auto& item : arran) {
        if (item.second.type == "integer") {
            ++countint;
        }
        else if (item.second.type == "real") {
            ++countreal;
        }
    }
    if (countint == 0 || countreal == 0) {
        std::cout << "error";
        return " ";
    }

    int num = rand() % countint + 1;
    auto it = arran.begin();
    while (num > 0) {
        // 如果当前项为int类型，num减一
        if (it->second.type == "integer") {
            --num;

            // 如果num变为0，读取
            if (num == 0) {
                par[0] = it->second;
            }
        }
        ++it;
    }
    num = rand() % countreal + 1;
    it = arran.begin();
    while (num > 0) {
        // 如果当前项为real类型，num减一
        if (it->second.type == "real") {
            --num;

            // 如果num变为0，读取
            if (num == 0) {
                par[1] = it->second;
            }
        }
        ++it;
    }
    int jud = rand() % 2;
    if (jud == 0) {
        int var = std::round(std::stod(par[1].value));
        Declaration.variables[par[0].name].value = std::to_string(var);
        return par[0].name + " := Round(" + par[1].name + ");\n";
    }
    else {
        int var = std::trunc(std::stod(par[1].value));
        Declaration.variables[par[0].name].value = std::to_string(var);
        return par[0].name + " := Trunc(" + par[1].name + ");\n";
    }
}

// 奇偶数
std::string StructureGenerator::odd(int input) {
    VariableInfo par[2];
    std::map<std::string, VariableInfo> arran = arrangement(input);
    if (arran.empty()) {
        std::cout << "The map is empty." << std::endl;
        return " ";
    }
    int countint = 0;
    int countbool = 0;
    for (const auto& item : arran) {
        if (item.second.type == "integer") {
            ++countint;
        }
        else if (item.second.type == "boolean") {
            ++countbool;
        }
    }
    if (countint == 0 || countbool == 0) {
        std::cout << "error";
        return " ";
    }

    int num = rand() % countint + 1;
    auto it = arran.begin();
    while (num > 0) {
        // 如果当前项为int类型，num减一
        if (it->second.type == "integer") {
            --num;

            // 如果num变为0，读取
            if (num == 0) {
                par[1] = it->second;
            }
        }
        ++it;
    }
    num = rand() % countbool + 1;
    it = arran.begin();
    while (num > 0) {
        // 如果当前项为boolean类型，num减一
        if (it->second.type == "boolean") {
            --num;

            // 如果num变为0，读取
            if (num == 0) {
                par[0] = it->second;
            }
        }
        ++it;
    }
    
    int var = std::stoi(par[1].value);
    if (var % 2 == 0) { //偶数
        Declaration.variables[par[0].name].value = "false";
    }
    else {  //奇数
        Declaration.variables[par[0].name].value = "true";
    }
    return par[0].name + " := Odd(" + par[1].name + ");\n";
}

std::string StructureGenerator::basicBlock(int input)
{
    int num = rand() % MAX_BASIC_BLOCK + MIN_BASIC_BLOCK;
    std::string result = "";
    for(int i = 1; i <= num; i++)
    {
        int randIndex = rand() % 2;
        switch(randIndex){
            case 0:
                result += calculate(input);
                break;
            case 1:
                result += assignment(input);
                break;
            default:
                break;
        }
    }
    return result;
}

std::string StructureGenerator::congeneration(std::map<std::string, VariableInfo> arran) {
    int num = rand() % MAX_CONDITION + MIN_CONDITION;
    if (num == 0)
    {
        num = 3;
    }
    
    std::vector<std::string> booleanOperators = { "and", "or" };
    std::vector<std::string> comparisonOperators = { "=", "<>", "<", ">", "<=", ">=" };
    std::string res = "";
    

    for (int i = 1; i <= num; i++) {
        auto it1 = arran.begin();
        std::advance(it1, rand() % arran.size());
        auto it2 = arran.begin();
        std::advance(it2, rand() % arran.size());

        std::string var1 = it1->second.name;
        std::string var2 = it2->second.name;
        std::string condition;

        // 如果两个变量都是int或real类型
        if ((it1->second.type == "integer" || it1->second.type == "real") && (it2->second.type == "integer" || it2->second.type == "real")) 
        {
            // 随机选择一个比较运算符
            std::string comparisonOperator = comparisonOperators[rand() % comparisonOperators.size()];

            // 构造条件表达式
            if (num == 1) {
                condition = var1 + " " + comparisonOperator + " " + var2 ;
            }
            else {
                condition = "(" + var1 + " " + comparisonOperator + " " + var2 + ")";
            }
        }
        // 如果两个变量都是boolean类型
        else if (it1->second.type == "boolean" && it2->second.type == "boolean") {
            int num1 = rand() % 3;
            switch (num1)
            {
                case 0:
                {
                    std::string logicOperator = booleanOperators[rand() % booleanOperators.size()];
                    if (num == 1) {
                        condition = var1 + " " + logicOperator + " " + var2;
                    }
                    else {
                        condition = "(" + var1 + " " + logicOperator + " " + var2 + ")";
                    }
                    break;
                }
                case 1:
                    condition = var1; break;

                case 2:
                    condition = var2; break;

                default:
                    break;
            }
        }
        // 如果两个变量都是char类型
        else if (it1->second.type == "char" &&it2->second.type == "char") {
            if (num == 1) {
                    condition = var1 + " = " + var2;
            }
            else {
                condition = "(" + var1 + " = " + var2 + ")";
            }
        }
        // 该情况可能性太大，故注释掉
        // else if (it1->second.type == "boolean" || it2->second.type == "boolean") {
        //     if (it1->second.type == "boolean") {
        //         condition = var1;
        //     }
        //     else {
        //         condition = var2;
        //     }
        // }
        else {
            i--;
            continue;
        }

        if (i > 1) {
            std::string logicOperator = booleanOperators[rand() % booleanOperators.size()];
            res = res + " " + logicOperator;
        }
        res = res + " " + condition;

    }
    if (res == ""){
        res = "true";
    }
    return res;
}

// if - else
std::string StructureGenerator::nestedIfStatement(int input, int depth) {
    // 获取给定作用域的变量
    std::string result = "";
    std::map<std::string, VariableInfo> arran = arrangement(input);

    // 如果变量不够，直接返回一个空的字符串
    if (arran.size() < 2) {
        return "";
    }

    std::string condition = congeneration(arran);

    result += "if " + condition + " then\n" + "begin\n";

    result += basicBlock(input) + "end\nelse";

    if(depth > 1) {
        result += " " + nestedIfStatement(input, depth - 1);
    }
    else {
        result += "\nbegin\n" + basicBlock(input) + "end;\n";
    }

    // 返回完整的 `if-else` 语句
    return result;
}



void StructureGenerator::printVariables() {
    Declaration.printVariables();
}

std::string StructureGenerator::block(int input)
{
    int index = rand() % 2;
    switch (index) {
    case 0:
        return basicBlock(input);
    case 1:
        return nestedIfStatement(input, rand() % MAX_IF_DEPTH + MIN_IF_DEPTH);
    default:
        return "";
    }
}

//// if
//std::string StructureGenerator::generateIfStatement(const std::string& variableName) {
//    std::string condition = variableName + " > " + generateRandomValue("integer"); // Assuming the variable is of a comparable type
//    std::string thenBranch = "    " + generateAssignment(variableName, "integer"); // Example assignment in the then branch
//    return "if " + condition + " then\n" + thenBranch + "end;\n";
//}
//
//// while
//std::string StructureGenerator::generateWhileLoop(const std::string& variableName) {
//    std::string condition = variableName + " < " + generateRandomValue("integer"); // Example condition
//    std::string body = "    " + generateAssignment(variableName, "integer"); // Example body
//    return "while " + condition + " do\nbegin\n" + body + "end;\n";
//}
//
//// for
//std::string StructureGenerator::generateForLoop(const std::string& variableName) {
//    std::string initialization = "for " + variableName + " := 1 to " + generateRandomValue("integer") + " do\nbegin\n";
//    std::string body = "    " + generateAssignment(variableName, "integer"); // Just for demonstration
//    return initialization + body + "end;\n";
//}

