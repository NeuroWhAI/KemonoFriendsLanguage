#include "WaiToken.h"

#include <sstream>

#include "Program.h"




WaiToken::WaiToken(const std::initializer_list<std::string>& tokens)
	: Token(tokens)
{

}

//###################################################################################################

std::size_t WaiToken::compile(const std::vector<std::string>& tokens,
	std::vector<std::string>::const_iterator itr,
	const std::string& code, Program& proc) const
{
	proc.pushCmd(Program::Types::WAI, code);


	std::istringstream sr{ code };

	proc.increaseWaiID();

	while (!sr.eof())
	{
		auto ch = sr.get();

		if (ch == '-')
		{
			proc.increaseWaiArg();
		}
		else if (ch == '~')
		{
			proc.increaseWaiID();
		}
	}


	return 0;
}

