#include "Tokenizer.h"

#include <stdexcept>




Tokenizer::Tokenizer()
{

}

//###################################################################################################

void Tokenizer::parse(std::istream& reader)
{
	m_tokens.clear();


	while (!reader.eof())
	{
		char ch = reader.get();

		if (ch == '#')
		{
			eatLineComment(reader);
		}
		else if (ch == '\"')
		{
			m_tokens.emplace_back("\"");
			readString(reader, m_tokens.back());
		}
		else if (ch == '\'')
		{
			m_tokens.emplace_back("\'");
			readNumbers(reader, m_tokens.back());
		}
		else if (isCommandChar(ch))
		{
			m_tokens.push_back({ ch });
			readCommand(reader, m_tokens.back());
		}
	}
}


const std::vector<std::string>& Tokenizer::getTokens() const
{
	return m_tokens;
}

//###################################################################################################

void Tokenizer::eatLineComment(std::istream& sr)
{
	while (!sr.eof() && sr.good())
	{
		if (sr.get() == '\n')
			break;
	}
}


void Tokenizer::readString(std::istream& sr, std::string& out)
{
	while (!sr.eof() && sr.good())
	{
		char ch = sr.get();

		out.push_back(ch);

		if (ch == '\"')
		{
			return;
		}
	}


	throw std::exception("Unexpected end of file in string.");
}


void Tokenizer::readNumbers(std::istream& sr, std::string& out)
{
	while (!sr.eof() && sr.good())
	{
		char ch = sr.get();

		out.push_back(ch);

		if (ch == '\'')
		{
			return;
		}
	}


	throw std::exception("Unexpected end of file in numbers.");
}


void Tokenizer::readCommand(std::istream& sr, std::string& out)
{
	while (!sr.eof())
	{
		char ch = sr.peek();

		if (isCommandChar(ch) == false)
			break;

		if (sr.good())
			out.push_back(sr.get());
	}
}

//###################################################################################################

bool Tokenizer::isCommandChar(char ch)
{
	return ((ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z')
		|| (ch >= '0' && ch <= '9')
		|| ch == '!' || ch == '?'
		|| ch == '-' || ch == '~'
		|| ch == '_'
		|| (ch & 0x80) != 0);
}

