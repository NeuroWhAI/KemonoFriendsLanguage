#ifndef __KFL__INTERPRETER_H__
#define __KFL__INTERPRETER_H__


#include <vector>
#include <stack>
#include <utility>
#include <sstream>
#include <functional>

#include "Program.h"




class Interpreter
{
private:
	struct CallStack
	{
		std::size_t head;
		std::size_t ptr;
		std::vector<char> ram;
	};

	using CmdFunc = void(Interpreter::*)(std::istringstream&);


public:
	Interpreter();


private:
	Program m_proc;
	char m_register;
	std::size_t m_head;
	std::vector<char> m_ram;
	std::size_t m_ptr;
	std::stack<CallStack> m_callStack;
	std::vector<CmdFunc> m_cmdList;


private:
	void registerCmd(Program::Types type, CmdFunc cmd);


public:
	void setProgram(const Program& proc);
	void run();


private:
	void incPtr();
	void decPtr();


private:
	void cmdNop(std::istringstream& sr);
	void cmdString(std::istringstream& sr);
	void cmdNumbers(std::istringstream& sr);
	void cmdFunc(std::istringstream& sr);
	void cmdCall(std::istringstream& sr);
	void cmdTanoshi(std::istringstream& sr);
	void cmdSugoi(std::istringstream& sr);
	void cmdUwa(std::istringstream& sr);
	void cmdWai(std::istringstream& sr);
	void cmdNanikore(std::istringstream& sr);
	void cmdOmoshiro(std::istringstream& sr);
	void cmdLala(std::istringstream& sr);
	void cmdMya(std::istringstream& sr);
	void cmdWriteReg(std::istringstream& sr);
	void cmdReadReg(std::istringstream& sr);
};


#endif