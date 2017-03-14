#include "Interpreter.h"

#include <iostream>
#include <numeric>
#include <stdexcept>




Interpreter::Interpreter()
	: m_register(0)
	, m_head(0)
	, m_ram(64, 0)
	, m_ptr(0)
{

}

//###################################################################################################

void Interpreter::setProgram(const Program& proc)
{
	// 초기화.
	m_register = 0;
	m_head = proc.getStartIndex();
	m_ram.clear();
	m_ram.resize(64, 0);
	m_ptr = 0;
	while (!m_callStack.empty())
		m_callStack.pop();
	m_uwaIDList.clear();
	m_uwaArgList.clear();
	m_waiIDList.clear();
	m_waiArgList.clear();


	auto& codeLine = proc.getCode();

	// 점프 테이블 작성.
	for (auto& code : codeLine)
	{
		m_uwaIDList.emplace_back(0);
		m_uwaArgList.emplace_back(0);
		m_waiIDList.emplace_back(0);
		m_waiArgList.emplace_back(0);
		
		if (code[0] != Program::CMD[0])
			continue;

		std::istringstream sr{ code };
		sr.get();
		const char subType = sr.get();

		if (subType == Program::UWA[0])
		{
			++m_uwaIDList.back();

			while (!sr.eof())
			{
				auto ch = sr.get();

				if (ch == '-')
				{
					if (m_uwaArgList.back() >= std::numeric_limits<char>::max())
						throw std::exception("Too big uwa-arg.");

					++m_uwaArgList.back();
				}
				else if (ch == '~')
				{
					++m_uwaIDList.back();
				}
			}
		}
		else if (subType == Program::WAI[0])
		{
			++m_waiIDList.back();

			while (!sr.eof())
			{
				auto ch = sr.get();

				if (ch == '-')
				{
					if (m_waiArgList.back() >= std::numeric_limits<char>::max())
						throw std::exception("Too big wai-arg.");

					++m_waiArgList.back();
				}
				else if (ch == '~')
				{
					++m_waiIDList.back();
				}
			}
		}
	}


	m_proc = proc;
}


void Interpreter::run()
{
	auto& proc = m_proc.getCode();

	while (m_head < proc.size())
	{
		auto& code = proc[m_head];

		std::istringstream sr{ code };
		const char type = sr.get();

		if (type == Program::NOP[0])
		{
			++m_head;
		}
		else if (type == Program::FUNC[0])
		{
			if (m_callStack.empty())
			{
				break;
			}
			else
			{
				const auto& bak = m_callStack.top();

				m_head = bak.first + 1;
				m_ptr = bak.second;

				m_callStack.pop();
			}
		}
		else if (type == Program::CALL[0])
		{
			m_callStack.push(std::make_pair(m_head, m_ptr));

			sr >> m_head;
		}
		else if (type == Program::CMD[0])
		{
			runCmd(sr);
		}
		else
		{
			throw std::exception("Invalid code.");
		}
	}
}

//###################################################################################################

void Interpreter::incPtr()
{
	++m_ptr;

	if (m_ptr >= m_ram.size())
	{
		m_ram.emplace_back(0);
	}
}


void Interpreter::decPtr()
{
	if (m_ptr > 0)
	{
		--m_ptr;
	}
}

//###################################################################################################

void Interpreter::runCmd(std::istringstream& sr)
{
	const auto subType = sr.get();


	if (subType == '\'')
	{
		cmdNumbers(sr);
	}
	else if (subType == '\"')
	{
		cmdString(sr);
	}
	else if (subType == Program::TAN[0])
	{
		cmdTanoshi(sr);
	}
	else if (subType == Program::SUG[0])
	{
		cmdSugoi(sr);
	}
	else if (subType == Program::UWA[0])
	{
		cmdUwa(sr);
	}
	else if (subType == Program::WAI[0])
	{
		cmdWai(sr);
	}
	else if (subType == Program::NANI[0])
	{
		cmdNanikore(sr);
	}
	else if (subType == Program::OMOS[0])
	{
		cmdOmoshiro(sr);
	}
	else if (subType == Program::LAL[0])
	{
		cmdLala(sr);
	}
	else if (subType == Program::SARU[0])
	{
		cmdWriteReg(sr);
	}
	else if (subType == Program::SABT[0])
	{
		cmdReadReg(sr);
	}
	else
	{
		//throw std::exception("Unknown command type.");
		++m_head;
	}
}


void Interpreter::cmdNumbers(std::istringstream& sr)
{
	bool first = true;
	std::string buffer;

	while (!sr.eof())
	{
		auto ch = sr.get();

		if (ch < '0' || ch > '9')
		{
			if (buffer.empty())
				continue;

			if (first)
			{
				first = false;
			}
			else
			{
				incPtr();
			}

			m_ram[m_ptr] = static_cast<char>(std::stoi(buffer) & 0x000000ff);

			buffer.clear();
		}
		else
		{
			buffer.push_back(ch);
		}
	}


	++m_head;
}


void Interpreter::cmdString(std::istringstream& sr)
{
	bool first = true;

	while (!sr.eof())
	{
		auto ch = sr.get();

		if (ch == '\"')
			break;

		if (first)
		{
			first = false;
		}
		else
		{
			incPtr();
		}

		m_ram[m_ptr] = ch;
	}


	++m_head;
}


void Interpreter::cmdTanoshi(std::istringstream & sr)
{
	while (!sr.eof())
	{
		auto ch = sr.get();

		if (ch == '-')
		{
			++m_ram[m_ptr];
		}
		else if (ch == '~')
		{
			m_ram[m_ptr] *= 2;
		}
		else if (ch == '!')
		{
			incPtr();
		}
	}


	++m_head;
}


void Interpreter::cmdSugoi(std::istringstream & sr)
{
	while (!sr.eof())
	{
		auto ch = sr.get();

		if (ch == '-')
		{
			--m_ram[m_ptr];
		}
		else if (ch == '~')
		{
			m_ram[m_ptr] /= 2;
		}
		else if (ch == '!')
		{
			decPtr();
		}
	}


	++m_head;
}


void Interpreter::cmdUwa(std::istringstream & sr)
{
	if (m_ram[m_ptr] == m_uwaArgList[m_head])
	{
		const auto endHead = m_proc.getCode().size();

		bool findMatch = false;

		for (auto h = m_head; h < endHead; ++h)
		{
			if (m_waiIDList[h] == m_uwaIDList[m_head])
			{
				m_head = h;

				findMatch = true;
				break;
			}
		}

		if (findMatch == false)
		{
			throw std::exception("Can't find wai.");
		}
	}
	else
	{
		++m_head;
	}
}


void Interpreter::cmdWai(std::istringstream & sr)
{
	if (m_ram[m_ptr] != m_waiArgList[m_head])
	{
		bool findMatch = false;

		for (auto h = m_head; h > 0; --h)
		{
			if (m_uwaIDList[h] == m_waiIDList[m_head])
			{
				m_head = h;

				findMatch = true;
				break;
			}
		}

		if (findMatch == false)
		{
			if (m_uwaIDList[0] == m_waiIDList[m_head])
			{
				m_head = 0;

				findMatch = true;
			}
			else
			{
				throw std::exception("Can't find uwa.");
			}
		}
	}
	else
	{
		++m_head;
	}
}


void Interpreter::cmdNanikore(std::istringstream & sr)
{
	bool first = true;

	while (!sr.eof())
	{
		auto ch = sr.get();

		if (ch == '?')
		{
			if (first)
			{
				first = false;
			}
			else
			{
				incPtr();
			}

			m_ram[m_ptr] = std::cin.get();
		}
	}


	++m_head;
}


void Interpreter::cmdOmoshiro(std::istringstream & sr)
{
	bool first = true;

	while (!sr.eof())
	{
		auto ch = sr.get();

		if (ch == '!')
		{
			if (first)
			{
				first = false;
			}
			else
			{
				incPtr();
			}

			std::cout << m_ram[m_ptr];
		}
	}


	++m_head;
}


void Interpreter::cmdLala(std::istringstream & sr)
{
	while (!sr.eof())
	{
		char ch = sr.get();

		if (ch == Program::LAL[0])
		{
			incPtr();
			m_ram[m_ptr] = m_ram[m_ptr - 1];
		}
	}


	++m_head;
}


void Interpreter::cmdWriteReg(std::istringstream & sr)
{
	m_register = m_ram[m_ptr];


	++m_head;
}


void Interpreter::cmdReadReg(std::istringstream & sr)
{
	m_ram[m_ptr] = m_register;


	++m_head;
}

