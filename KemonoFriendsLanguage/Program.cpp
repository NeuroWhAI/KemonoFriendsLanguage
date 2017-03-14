#include "Program.h"




const std::string Program::NOP = "$";
const std::string Program::FUNC = "f";
const std::string Program::CALL = "c";
const std::string Program::CMD = "*";
const std::string Program::TAN = "t";
const std::string Program::SUG = "s";
const std::string Program::UWA = "u";
const std::string Program::WAI = "w";
const std::string Program::NANI = "n";
const std::string Program::OMOS = "o";
const std::string Program::LAL = "l";
const std::string Program::SARU = "<";
const std::string Program::SABT = ">";

//###################################################################################################

Program::Program()
	: m_beginIndex(0)
{

}

//###################################################################################################

void Program::setMain(std::size_t index)
{
	m_beginIndex = index;
}


void Program::pushNop()
{
	m_code.emplace_back(NOP);
}


void Program::pushFunc()
{
	m_code.emplace_back(FUNC);
}


void Program::pushCall(std::size_t destIndex)
{
	m_code.emplace_back(CALL + std::to_string(destIndex));
}


void Program::pushCmd(const std::string& cmd)
{
	m_code.emplace_back(CMD + cmd);
}


void Program::pushCmd(const std::string& subType, const std::string& cmd)
{
	m_code.emplace_back(CMD + subType + cmd);
}

//###################################################################################################

std::size_t Program::getStartIndex() const
{
	return m_beginIndex;
}


const std::vector<std::string>& Program::getCode() const
{
	return m_code;
}

