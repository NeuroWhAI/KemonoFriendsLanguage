#include "Compiler.h"

#include <stdexcept>
#include <algorithm>




Compiler::Compiler()
{
	m_funcTokens.emplace_back("friends");
	m_funcTokens.emplace_back("프렌즈");

	m_callTokens.emplace_back("sandstar");
	m_callTokens.emplace_back("샌드스타");

	m_mainTokens.emplace_back("youkoso");
	m_mainTokens.emplace_back("요코소");

	m_tanoshiTokens.emplace_back("ta");
	m_tanoshiTokens.emplace_back("타");

	m_sugoiTokens.emplace_back("sugo");
	m_sugoiTokens.emplace_back("스고");

	m_uwaTokens.emplace_back("u");
	m_uwaTokens.emplace_back("우");

	m_waiTokens.emplace_back("wa");
	m_waiTokens.emplace_back("와");

	m_naniTokens.emplace_back("nanikore");
	m_naniTokens.emplace_back("나니코레");

	m_omoshiTokens.emplace_back("omoshiro");
	m_omoshiTokens.emplace_back("오모시로");

	m_lalaTokens.emplace_back("la");
	m_lalaTokens.emplace_back("라");
	m_lalaTokens.emplace_back("랄");

	m_writeRegTokens.emplace_back("shaberu");
	m_writeRegTokens.emplace_back("샤베루");

	m_readRegTokens.emplace_back("Shabetta");
	m_readRegTokens.emplace_back("Shabeta");
	m_readRegTokens.emplace_back("샤벳타");
	m_readRegTokens.emplace_back("샤베타");
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
		if (isToken(m_funcTokens, *itr))
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
		else if (isToken(m_mainTokens, *itr))
		{
			// 프로그램 시작 위치 설정.
			program.setMain(index + 1);
		}
	}


	itr = tokens.begin();
	index = 0;

	// 중간 코드 생성.
	for (; itr != tokens.end(); ++itr, ++index)
	{
		if (isToken(m_callTokens, *itr))
		{
			if (index + 1 >= tokens.size())
				throw std::exception("There is no name for function-call.");

			const auto& funcName = tokens[index + 1];

			auto funcItr = m_funcTable.find(funcName);
			if (funcItr == m_funcTable.end())
				throw std::exception("There is no function.");

			program.pushNop();
			program.pushCall(funcItr->second);

			// 다음은 이름이므로 건너 뜀.
			++itr;
			++index;
		}
		else if (isToken(m_funcTokens, *itr))
		{
			program.pushNop();
			program.pushFunc();

			// 다음은 이름이므로 건너 뜀.
			++itr;
			++index;
		}
		else if (isToken(m_mainTokens, *itr))
		{
			program.pushFunc();
		}
		else if (startWithToken(m_tanoshiTokens, *itr))
		{
			program.pushCmd(Program::TAN, *itr);
		}
		else if (startWithToken(m_sugoiTokens, *itr))
		{
			program.pushCmd(Program::SUG, *itr);
		}
		else if (startWithToken(m_uwaTokens, *itr))
		{
			program.pushCmd(Program::UWA, *itr);
		}
		else if (startWithToken(m_waiTokens, *itr))
		{
			program.pushCmd(Program::WAI, *itr);
		}
		else if (startWithToken(m_naniTokens, *itr))
		{
			program.pushCmd(Program::NANI, *itr);
		}
		else if (startWithToken(m_omoshiTokens, *itr))
		{
			program.pushCmd(Program::OMOS, *itr);
		}
		else if (startWithToken(m_lalaTokens, *itr))
		{
			std::string lala;
			for (std::size_t laOffset = 0; laOffset < itr->size();)
			{
				bool findTok = false;

				for (auto& tok : m_lalaTokens)
				{
					if (itr->find(tok, laOffset) == 0)
					{
						laOffset += tok.length();

						lala.push_back(Program::LAL[0]);

						findTok = true;
						break;
					}
				}

				if (findTok == false)
				{
					++laOffset;
				}
			}

			program.pushCmd(Program::LAL, lala);
		}
		else if (isToken(m_writeRegTokens, *itr))
		{
			program.pushCmd(Program::SARU, *itr);
		}
		else if (isToken(m_readRegTokens, *itr))
		{
			program.pushCmd(Program::SABT, *itr);
		}
		else
		{
			program.pushCmd(*itr);
		}
	}


	// 마지막에 선언된 함수가 반환될 수 있도록 함.
	program.pushFunc();


	return program;
}

//###################################################################################################

bool Compiler::isToken(const std::vector<std::string>& tokens, const std::string& text) const
{
	return (std::find(tokens.begin(), tokens.end(), text) != tokens.end());
}


bool Compiler::startWithToken(const std::vector<std::string>& tokens, const std::string& text) const
{
	for (auto& tok : tokens)
	{
		if (text.find(tok) == 0)
			return true;
	}

	return false;
}

