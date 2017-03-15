#include "Compiler.h"

#include <stdexcept>
#include <algorithm>
#include <sstream>




Compiler::Compiler()
	: m_tokenList(
{
	&m_funcToken, &m_callToken, &m_mainToken, &m_tanoshiToken, &m_sugoiToken,
	&m_uwaToken, &m_waiToken, &m_naniToken, &m_omoshiToken, &m_lalaToken,
	&m_writeRegToken, &m_readRegToken,
}
	)
	
	, m_funcToken({ "friends", "프렌즈" })
	, m_callToken(m_funcTable, { "sandstar", "샌드스타" })
	, m_mainToken({ "youkoso", "요코소" })
	, m_tanoshiToken(Program::TAN, { "ta", "타" })
	, m_sugoiToken(Program::SUG, { "sugo", "스고", "슷고" })
	, m_uwaToken({ "u", "우" })
	, m_waiToken({ "wa", "와" })
	, m_naniToken(Program::NANI, { "nanikore", "나니코레" })
	, m_omoshiToken(Program::OMOS, { "omoshiro", "오모시로" })
	, m_lalaToken({ "la", "라", "랄" })
	, m_writeRegToken(Program::SARU, { "shaberu", "샤베루" })
	, m_readRegToken(Program::SABT, { "Shabetta", "Shabeta", "샤벳타", "샤베타" })
{
	
}

//###################################################################################################

Program Compiler::compile(const std::vector<std::string>& tokens)
{
	// 초기화.
	m_funcTable.clear();


	Program program;


	auto itr = tokens.begin();
	std::size_t index = 0;

	// 함수 테이블 작성.
	for (; itr != tokens.end(); ++itr, ++index)
	{
		if (m_funcToken.check(*itr))
		{
			if (index + 1 >= tokens.size())
				throw std::exception("There is no name for function.");

			auto result = m_funcTable.insert(std::make_pair(tokens[index + 1], index + 2));

			if(result.second == false)
				throw std::exception("Function already exists.");

			// 다음은 이름이므로 건너 뜀.
			++itr;
			++index;
		}
		else if (m_mainToken.check(*itr))
		{
			// 프로그램 시작 위치 설정.
			program.setMain(index + 1);
		}
	}


	itr = tokens.begin();
	index = 0;
	std::size_t skipCount = 0;

	// 중간 코드 생성.
	for (; itr != tokens.end(); ++itr, ++index)
	{
		program.appendUwaiList();


		if (skipCount > 0)
		{
			--skipCount;
			continue;
		}


		bool findToken = false;

		for (auto& tok : m_tokenList)
		{
			auto result = tok->checkAndCompile(itr, *itr, program);

			if (result.first)
			{
				skipCount += result.second;

				findToken = true;
				break;
			}
		}

		if (findToken == false)
		{
			program.pushCmd(*itr);
		}
	}


	// 마지막에 선언된 함수가 반환될 수 있도록 함.
	program.pushFunc();


	return program;
}

