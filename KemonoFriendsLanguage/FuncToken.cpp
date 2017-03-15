#include "FuncToken.h"

#include "Program.h"




FuncToken::FuncToken(const std::initializer_list<std::string>& tokens)
	: Token(tokens)
{

}

//###################################################################################################

std::size_t FuncToken::compile(const std::vector<std::string>& tokens,
	std::vector<std::string>::const_iterator itr,
	const std::string& code, Program& proc) const
{
	proc.pushNop();
	proc.pushFunc();


	// 다음은 이름이므로 건너 뜀.
	return 1;
}

