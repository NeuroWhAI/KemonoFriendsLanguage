#include "Token.h"

#include <algorithm>




Token::Token(const std::initializer_list<std::string>& tokens)
	: m_tokens(tokens)
{

}

//###################################################################################################

bool Token::check(const std::string& code) const
{
	for (auto& tok : m_tokens)
	{
		if (code.find(tok) == 0)
		{
			return true;
		}
	}

	return false;
}


std::pair<bool, std::size_t> Token::checkAndCompile(std::vector<std::string>::const_iterator itr,
	const std::string& code, Program& proc) const
{
	if (check(code))
	{
		auto skipCount = compile(m_tokens, itr, code, proc);

		return std::make_pair(true, skipCount);
	}

	return std::make_pair(false, 0);
}

