#include <stdio.h>
#include <string>
#include "ValueGenerator.h"
#include "DeclarationManager.h"
#include "StructureGenerator.h"
#include <iostream>


int main(void) {
	srand(static_cast<unsigned int>(time(nullptr)));
	//权值生成模块使用
	/*ValueGenerator generator;
	std::string value = generator.generateRandomData(3);
	std::cout << value;*/

	//变量及函数声明模块使用，目前仅变量
	/*VariableDeclarationManager generator;
	std::string name;
	name = generator.declareVariable(1);
	name = generator.declareVariable(0);
	name = generator.declareVariable(3);
	generator.printVariables();*/
	int num_var = rand() % MAX_VAR + MIN_VAR;
	int num_func = rand() % MAX_FUNC + MIN_FUNC;
	int num_assign = rand() % MAX_ASSIGN + MIN_ASSIGN;
	int num_block = rand() % MAX_BLOCK + MIN_BLOCK;
	int num_print = rand() % MAX_PRINT + MIN_PRINT;
	

	StructureGenerator generator;
	std::cout << "program main;" << std::endl;
	std::cout << "//---------------start declare---------------" << std::endl;
	std::cout << "\nvar" << std::endl;
	std::string name;
	for (int i = 0; i < num_block * MAX_FOR_DEPTH; i++) {
		std::cout << generator.declare(0, INDEX_INT);
	}
	for (int i = 0; i < num_var; i++) {
		std::cout << generator.declare(0);
	}
	std::cout << "//---------------start func declare---------------" << std::endl;
	for (int i = 1; i <= num_func; i++) {
		std::cout << std::endl;
		std::cout << generator.declareSubFunc(i)<< std::endl;;
	}
	std::cout << "\nbegin" << std::endl;
	std::cout << "//---------------start init---------------" << std::endl;
	for(const auto& item: generator.arrangement(0)){
		std::cout << item.second.name << " := " << item.second.value << ";" << std::endl;
	}
	std::cout << "//---------------start assign---------------" << std::endl;
	for (int i = 0; i < num_assign; i++) {
		std::cout << generator.assignment(0);
	}
	std::cout << "//---------------start calc---------------" << std::endl;
	for (int i = 0; i < num_block; i++) {
		std::cout << generator.block(0);
	}
	
	std::cout << "//---------------start print---------------" << std::endl;
	for (int i = 0; i < num_print; i++) {
		std::cout << generator.write(0);
	}

	std::cout << "end."<< std::endl;
	// std::cout << "---------------print results:---------------" << std::endl;
	// generator.printVariables();
	

	return 0;
}