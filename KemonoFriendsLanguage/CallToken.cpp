#include "CallToken.h"

#include "Program.h"




CallToken::CallToken(const std::unordered_map<std::string, std::size_t>& funcTable,
	const std::initializer_list<std::string>& tokens)
	: Token(tokens)
	, m_funcTable(funcTable)
{

}

//###################################################################################################

std::size_t CallToken::compile(const std::vector<std::string>& tokens,
	std::vector<std::string>::const_iterator itr,
	const std::string& code, Program& proc) const
{
	const auto& funcName = itr[1];


	auto funcItr = m_funcTable.find(funcName);
	if (funcItr == m_funcTable.end())
		throw std::exception("There is no function.");


	proc.pushCmd(Program::Types::NOP);
	proc.pushCall(funcItr->second);


	// 다음은 이름이므로 건너 뜀.
	return 1;
}

