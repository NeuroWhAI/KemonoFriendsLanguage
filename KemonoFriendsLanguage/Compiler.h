#ifndef __KFL__COMPILER_H__
#define __KFL__COMPILER_H__


#include <string>
#include <vector>
#include <unordered_map>

#include "AllTokens.h"
#include "Program.h"




class Compiler
{
public:
	Compiler();


private:
	const std::vector<Token*> m_tokenList;
	FuncToken m_funcToken;
	CallToken m_callToken;
	MainToken m_mainToken;
	CmdToken m_tanoshiToken;
	CmdToken m_sugoiToken;
	UwaToken m_uwaToken;
	WaiToken m_waiToken;
	CmdToken m_naniToken;
	CmdToken m_omoshiToken;
	RepeatToken m_lalaToken;
	RepeatToken m_myaToken;
	CmdToken m_writeRegToken;
	CmdToken m_readRegToken;


private:
	std::unordered_map<std::string, std::size_t> m_funcTable;


public:
	Program compile(const std::vector<std::string>& tokens);
};


#endif