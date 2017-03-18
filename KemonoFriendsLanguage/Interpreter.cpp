#include "Interpreter.h"

#include <iostream>
#include <numeric>
#include <stdexcept>
#include <algorithm>

#include "RepeatToken.h"




Interpreter::Interpreter()
	: m_register(0)
	, m_head(0)
	, m_ram(64, 0)
	, m_ptr(0)
	, m_cmdList(static_cast<std::size_t>(Program::Types::Count), &Interpreter::cmdNop)
{
	registerCmd(Program::Types::NOP, &Interpreter::cmdNop);
	registerCmd(Program::Types::STR, &Interpreter::cmdString);
	registerCmd(Program::Types::NUM, &Interpreter::cmdNumbers);
	registerCmd(Program::Types::FUNC, &Interpreter::cmdFunc);
	registerCmd(Program::Types::CALL, &Interpreter::cmdCall);
	registerCmd(Program::Types::TAN, &Interpreter::cmdTanoshi);
	registerCmd(Program::Types::SUG, &Interpreter::cmdSugoi);
	registerCmd(Program::Types::UWA, &Interpreter::cmdUwa);
	registerCmd(Program::Types::WAI, &Interpreter::cmdWai);
	registerCmd(Program::Types::NANI, &Interpreter::cmdNanikore);
	registerCmd(Program::Types::OMOS, &Interpreter::cmdOmoshiro);
	registerCmd(Program::Types::LAL, &Interpreter::cmdLala);
	registerCmd(Program::Types::MYA, &Interpreter::cmdMya);
	registerCmd(Program::Types::SARU, &Interpreter::cmdWriteReg);
	registerCmd(Program::Types::SABT, &Interpreter::cmdReadReg);
}

//###################################################################################################

void Interpreter::registerCmd(Program::Types type, CmdFunc cmd)
{
	m_cmdList[static_cast<int>(type)] = cmd;
}

//###################################################################################################

void Interpreter::setProgram(const Program& proc)
{
	// √ ±‚»≠.
	m_register = 0;
	m_head = proc.getStartIndex();
	m_ram.clear();
	m_ram.resize(64, 0);
	m_ptr = 0;
	while (!m_callStack.empty())
		m_callStack.pop();


	m_proc = proc;
}


void Interpreter::run()
{
	auto& proc = m_proc.getCode();

	while (m_head < proc.size())
	{
		auto& code = proc[m_head];

		std::istringstream sr{ code };
		const auto type = sr.get() - Program::TYPE_TO_CHAR;

		if (type >= 0 && static_cast<std::size_t>(type) < m_cmdList.size())
		{
			(this->*m_cmdList[type])(sr);
		}
		else
		{
			throw std::exception("Unknown command.");
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

void Interpreter::cmdNop(std::istringstream& sr)
{
	++m_head;
}


void Interpreter::cmdString(std::istringstream& sr)
{
	// Pop first '"'
	sr.get();


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


void Interpreter::cmdNumbers(std::istringstream& sr)
{
	bool first = true;
	std::string buffer;

	while (!sr.eof())
	{
		auto ch = sr.get();

		if (ch >= '0' && ch <= '9')
		{
			buffer.push_back(ch);
		}
		else if (buffer.empty() && (ch == '-' || ch == '+'))
		{
			buffer.push_back(ch);
		}
		else
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
	}


	++m_head;
}


void Interpreter::cmdFunc(std::istringstream& sr)
{
	if (m_callStack.empty())
	{
		// Exit.
		m_head = m_proc.getCode().size();
	}
	else
	{
		const auto& bak = m_callStack.top();

		m_head = bak.head + 1;
		m_ptr = bak.ptr;
		std::copy(bak.ram.cbegin(), bak.ram.cend(), m_ram.begin() + (bak.ptr + 1));

		m_callStack.pop();
	}
}


void Interpreter::cmdCall(std::istringstream& sr)
{
	CallStack bak;
	bak.head = m_head;
	bak.ptr = m_ptr;
	bak.ram.assign(m_ram.begin() + (m_ptr + 1), m_ram.end());

	m_callStack.emplace(std::move(bak));

	sr >> m_head;
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
	if (m_ram[m_ptr] == m_proc.getUwaArg(m_head))
	{
		const auto endHead = m_proc.getCode().size();

		bool findMatch = false;

		const auto targetID = m_proc.getUwaID(m_head);

		for (auto h = m_head; h < endHead; ++h)
		{
			if (m_proc.getWaiID(h) == targetID)
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
	if (m_ram[m_ptr] != m_proc.getWaiArg(m_head))
	{
		bool findMatch = false;

		const auto targetID = m_proc.getWaiID(m_head);

		for (auto h = m_head; h > 0; --h)
		{
			if (m_proc.getUwaID(h) == targetID)
			{
				m_head = h;

				findMatch = true;
				break;
			}
		}

		if (findMatch == false)
		{
			if (m_proc.getUwaID(0) == targetID)
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

			std::cout.put(m_ram[m_ptr]);
		}
	}


	++m_head;
}


void Interpreter::cmdLala(std::istringstream & sr)
{
	auto src = m_ram[m_ptr];

	while (!sr.eof())
	{
		char ch = sr.get();

		if (ch == RepeatToken::ONE_CHAR_ONE_TOKEN)
		{
			incPtr();
		}
	}

	m_ram[m_ptr] = src;


	++m_head;
}


void Interpreter::cmdMya(std::istringstream & sr)
{
	auto src = m_ram[m_ptr];

	while (!sr.eof())
	{
		char ch = sr.get();

		if (ch == RepeatToken::ONE_CHAR_ONE_TOKEN)
		{
			decPtr();
		}
	}

	m_ram[m_ptr] = src;


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

