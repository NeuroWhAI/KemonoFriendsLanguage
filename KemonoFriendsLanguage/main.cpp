#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <fstream>
#include <stdexcept>

#include "Compiler.h"
#include "Interpreter.h"




bool isCommandChar(char ch)
{
	return ((ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z')
		|| (ch >= '0' && ch <= '9')
		|| ch == '!' || ch == '?'
		|| ch == '-' || ch == '~'
		|| ch == '_'
		|| (ch & 0x80) != 0);
}


void eatLineComment(std::istream& sr)
{
	while (!sr.eof() && sr.good())
	{
		if (sr.get() == '\n')
			break;
	}
}


void readString(std::istream& sr, std::string& out)
{
	while (!sr.eof() && sr.good())
	{
		char ch = sr.get();

		out.push_back(ch);

		if (ch == '\"')
		{
			return;
		}
	}


	throw std::exception("Unexpected end of file in string.");
}


void readNumbers(std::istream& sr, std::string& out)
{
	while (!sr.eof() && sr.good())
	{
		char ch = sr.get();

		out.push_back(ch);

		if (ch == '\'')
		{
			return;
		}
	}


	throw std::exception("Unexpected end of file in numbers.");
}


void readCommand(std::istream& sr, std::string& out)
{
	while (!sr.eof())
	{
		char ch = sr.peek();

		if (isCommandChar(ch) == false)
			break;

		if (sr.good())
			out.push_back(sr.get());
	}
}


int main(int argc, char** argv)
{
	std::ifstream fr;

	if (argc >= 2)
		fr.open(argv[1]);
	else
		fr.open("code.txt");

	if (fr.is_open() == false)
	{
		std::cout << "Can\'t open file." << std::endl;
		return 0;
	}


	std::vector<std::string> tokens;

	try
	{
		while (!fr.eof())
		{
			char ch = fr.get();

			if (ch == '#')
			{
				eatLineComment(fr);
			}
			else if (ch == '\"')
			{
				tokens.emplace_back("\"");
				readString(fr, tokens.back());
			}
			else if (ch == '\'')
			{
				tokens.emplace_back("\'");
				readNumbers(fr, tokens.back());
			}
			else if (isCommandChar(ch))
			{
				tokens.push_back({ ch });
				readCommand(fr, tokens.back());
			}
		}
	}
	catch (std::exception& exp)
	{
		std::cout << "Error!" << std::endl;
		std::cout << exp.what() << std::endl;

		return 0;
	}


	try
	{
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

		return 0;
	}


#ifdef _DEBUG
	system("pause");
#endif // _DEBUG


	return 0;
}

