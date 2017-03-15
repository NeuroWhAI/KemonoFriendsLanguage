#include "LalaToken.h"

#include "Program.h"




LalaToken::LalaToken(const std::initializer_list<std::string>& tokens)
	: Token(tokens)
{

}

//###################################################################################################

std::size_t LalaToken::compile(const std::vector<std::string>& tokens,
	std::vector<std::string>::const_iterator itr,
	const std::string& code, Program& proc) const
{
	std::string lala;

	for (std::size_t laOffset = 0; laOffset < code.size();)
	{
		bool findTok = false;

		for (auto& tok : tokens)
		{
			if (code.find(tok, laOffset) == laOffset)
			{
				laOffset += tok.length();

				lala.push_back(Program::LAL[0]);

				findTok = true;
				break;
			}
		}

		if (findTok == false)
		{
			++laOffset;
		}
	}

	proc.pushCmd(Program::LAL, lala);


	return 0;
}

