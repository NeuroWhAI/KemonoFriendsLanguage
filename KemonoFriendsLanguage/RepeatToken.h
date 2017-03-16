#ifndef __KFL__REPEAT_TOKEN_H__
#define __KFL__REPEAT_TOKEN_H__


#include "Token.h"




class RepeatToken : public Token
{
public:
	RepeatToken(const std::string& type, const std::initializer_list<std::string>& tokens);


private:
	std::string m_type;


protected:
	virtual std::size_t compile(const std::vector<std::string>& tokens,
		std::vector<std::string>::const_iterator itr,
		const std::string& code, Program& proc) const override;
};


#endif