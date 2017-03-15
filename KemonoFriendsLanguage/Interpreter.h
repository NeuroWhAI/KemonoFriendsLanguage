#ifndef __KFL__INTERPRETER_H__
#define __KFL__INTERPRETER_H__


#include <vector>
#include <stack>
#include <utility>
#include <sstream>

#include "Program.h"




class Interpreter
{
public:
	Interpreter();


private:
	Program m_proc;
	char m_register;
	std::size_t m_head;
	std::vector<char> m_ram;
	std::size_t m_ptr;
	std::stack<std::pair<std::size_t, std::size_t>> m_callStack;


public:
	void setProgram(const Program& proc);
	void run();


private:
	void incPtr();
	void decPtr();


private:
	void runCmd(std::istringstream& sr);
	void cmdNumbers(std::istringstream& sr);
	void cmdString(std::istringstream& sr);
	void cmdTanoshi(std::istringstream& sr);
	void cmdSugoi(std::istringstream& sr);
	void cmdUwa(std::istringstream& sr);
	void cmdWai(std::istringstream& sr);
	void cmdNanikore(std::istringstream& sr);
	void cmdOmoshiro(std::istringstream& sr);
	void cmdLala(std::istringstream& sr);
	void cmdWriteReg(std::istringstream& sr);
	void cmdReadReg(std::istringstream& sr);
};


#endif