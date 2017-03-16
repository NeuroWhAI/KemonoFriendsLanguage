#ifndef __KFL__REPEAT_TOKEN_H__
#define __KFL__REPEAT_TOKEN_H__


#include "Token.h"

#include "Program.h"




class RepeatToken : public Token
{
public:
	static const char ONE_CHAR_ONE_TOKEN = '-';


public:
	RepeatToken(Program::Types type, const std::initializer_list<std::string>& tokens);


private:
	Program::Types m_type;


protected:
	virtual std::size_t compile(const std::vector<std::string>& tokens,
		std::vector<std::string>::const_iterator itr,
		const std::string& code, Program& proc) const override;
};


#endif