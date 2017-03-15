#include "CmdToken.h"

#include "Program.h"




CmdToken::CmdToken(const std::string& type, const std::initializer_list<std::string>& tokens)
	: Token(tokens)
	, m_type(type)
{

}

//###################################################################################################

std::size_t CmdToken::compile(const std::vector<std::string>& tokens,
	std::vector<std::string>::const_iterator itr,
	const std::string& code, Program& proc) const
{
	proc.pushCmd(m_type, code);

	
	return 0;
}

