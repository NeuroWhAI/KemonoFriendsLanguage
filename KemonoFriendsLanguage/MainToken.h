#ifndef __KFL__MAIN_TOKEN_H__
#define __KFL__MAIN_TOKEN_H__


#include "Token.h"




class MainToken : public Token
{
public:
	MainToken(const std::initializer_list<std::string>& tokens);


protected:
	virtual std::size_t compile(const std::vector<std::string>& tokens,
		std::vector<std::string>::const_iterator itr,
		const std::string& code, Program& proc) const override;
};


#endif