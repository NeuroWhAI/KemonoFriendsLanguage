#include "UwaToken.h"

#include <sstream>

#include "Program.h"




UwaToken::UwaToken(const std::initializer_list<std::string>& tokens)
	: Token(tokens)
{

}

//###################################################################################################

std::size_t UwaToken::compile(const std::vector<std::string>& tokens,
	std::vector<std::string>::const_iterator itr,
	const std::string& code, Program& proc) const
{
	proc.pushCmd(Program::UWA, code);


	std::istringstream sr{ code };

	proc.increaseUwaID();

	while (!sr.eof())
	{
		auto ch = sr.get();

		if (ch == '-')
		{
			proc.increaseUwaArg();
		}
		else if (ch == '~')
		{
			proc.increaseUwaID();
		}
	}


	return 0;
}

