#ifndef __KFL__TOKENIZER_H__
#define __KFL__TOKENIZER_H__


#include <vector>
#include <string>
#include <istream>




class Tokenizer
{
public:
	Tokenizer();


public:
	std::vector<std::string> m_tokens;


public:
	void parse(std::istream& reader);
	const std::vector<std::string>& getTokens() const;


private:
	void eatLineComment(std::istream& sr);
	void readString(std::istream& sr, std::string& out);
	void readNumbers(std::istream& sr, std::string& out);
	void readCommand(std::istream& sr, std::string& out);


private:
	bool isCommandChar(char ch);
};


#endif