#include "RepeatToken.h"

#include "Program.h"




RepeatToken::RepeatToken(const std::string& type, const std::initializer_list<std::string>& tokens)
	: Token(tokens)
	, m_type(type)
{

}

//###################################################################################################

std::size_t RepeatToken::compile(const std::vector<std::string>& tokens,
	std::vector<std::string>::const_iterator itr,
	const std::string& code, Program& proc) const
{
	std::string cmd;

	for (std::size_t laOffset = 0; laOffset < code.size();)
	{
		bool findTok = false;

		for (auto& tok : tokens)
		{
			if (code.find(tok, laOffset) == laOffset)
			{
				laOffset += tok.length();

				cmd.push_back(m_type[0]);

				findTok = true;
				break;
			}
		}

		if (findTok == false)
		{
			++laOffset;
		}
	}

	proc.pushCmd(m_type, cmd);


	return 0;
}

