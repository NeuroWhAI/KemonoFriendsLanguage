#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <fstream>
#include <stdexcept>

#include "Tokenizer.h"
#include "Compiler.h"
#include "Interpreter.h"




int main(int argc, char** argv)
{
	std::ifstream fr;

#ifdef _DEBUG
	fr.open("../Examples/hello.txt");
#else
	if (argc >= 2)
		fr.open(argv[1]);
	else
		fr.open("code.txt");
#endif

	if (fr.is_open() == false)
	{
		std::cout << "Can\'t open file." << std::endl;
		return 0;
	}


	try
	{
		Tokenizer tokenizer;
		tokenizer.parse(fr);
		auto& tokens = tokenizer.getTokens();


		Compiler com;
		auto program = com.compile(tokens);


		Interpreter interpreter;
		interpreter.setProgram(program);
		interpreter.run();
	}
	catch (std::exception& exp)
	{
		std::cout << "Error!" << std::endl;
		std::cout << exp.what() << std::endl;
	}


#ifdef _DEBUG
	std::cout << std::endl << "Press the Enter key to exit." << std::endl;
	std::cin.get();
#endif // _DEBUG


	return 0;
}

