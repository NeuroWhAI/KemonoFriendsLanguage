#ifndef __KFL__CALL_TOKEN_H__
#define __KFL__CALL_TOKEN_H__


#include <unordered_map>

#include "Token.h"




class CallToken : public Token
{
public:
	CallToken(const std::unordered_map<std::string, std::size_t>& funcTable,
		const std::initializer_list<std::string>& tokens);


private:
	const std::unordered_map<std::string, std::size_t>& m_funcTable;


protected:
	virtual std::size_t compile(const std::vector<std::string>& tokens,
		std::vector<std::string>::const_iterator itr,
		const std::string& code, Program& proc) const override;
};


#endif