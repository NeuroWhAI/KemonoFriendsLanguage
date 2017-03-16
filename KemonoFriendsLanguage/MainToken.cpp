#include "MainToken.h"

#include "Program.h"




MainToken::MainToken(const std::initializer_list<std::string>& tokens)
	: Token(tokens)
{

}

//###################################################################################################

std::size_t MainToken::compile(const std::vector<std::string>& tokens,
	std::vector<std::string>::const_iterator itr,
	const std::string& code, Program& proc) const
{
	proc.pushCmd(Program::Types::FUNC);


	return 0;
}

