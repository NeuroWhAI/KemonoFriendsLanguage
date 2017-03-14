#ifndef __KFL__COMPILER_H__
#define __KFL__COMPILER_H__


#include <string>
#include <vector>
#include <unordered_map>

#include "Program.h"




class Compiler
{
public:
	Compiler();


private:
	std::vector<std::string> m_funcTokens;
	std::vector<std::string> m_callTokens;
	std::vector<std::string> m_mainTokens;
	std::vector<std::string> m_tanoshiTokens;
	std::vector<std::string> m_sugoiTokens;
	std::vector<std::string> m_uwaTokens;
	std::vector<std::string> m_waiTokens;
	std::vector<std::string> m_naniTokens;
	std::vector<std::string> m_omoshiTokens;
	std::vector<std::string> m_lalaTokens;
	std::vector<std::string> m_writeRegTokens;
	std::vector<std::string> m_readRegTokens;


private:
	std::unordered_map<std::string, std::size_t> m_funcTable;


public:
	Program compile(const std::vector<std::string>& tokens);


private:
	bool isToken(const std::vector<std::string>& tokens, const std::string& text) const;
	bool startWithToken(const std::vector<std::string>& tokens, const std::string& text) const;
};


#endif