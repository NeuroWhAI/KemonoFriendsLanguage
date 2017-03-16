#include "Program.h"

#include <numeric>
#include <stdexcept>




Program::Program()
	: m_beginIndex(0)
{

}

//###################################################################################################

void Program::setMain(std::size_t index)
{
	m_beginIndex = index;
}


void Program::pushCall(std::size_t destIndex)
{
	const char typeChar = static_cast<char>(TYPE_TO_CHAR + static_cast<int>(Types::CALL));

	m_code.emplace_back(std::string({ typeChar }) + std::to_string(destIndex));
}


void Program::pushCmd(Types type)
{
	const char typeChar = static_cast<char>(TYPE_TO_CHAR + static_cast<int>(type));

	m_code.emplace_back(std::string({ typeChar }));
}


void Program::pushCmd(Types type, const std::string& arg)
{
	const char typeChar = static_cast<char>(TYPE_TO_CHAR + static_cast<int>(type));

	m_code.emplace_back(std::string({ typeChar }) + arg);
}

//###################################################################################################

void Program::appendUwaiList()
{
	m_uwaIDList.emplace_back(0);
	m_uwaArgList.emplace_back(0);
	m_waiIDList.emplace_back(0);
	m_waiArgList.emplace_back(0);
}


void Program::increaseUwaID()
{
	++m_uwaIDList.back();
}


void Program::increaseUwaArg()
{
	if (m_uwaArgList.back() >= std::numeric_limits<char>::max())
		throw std::exception("Too big uwa-arg.");

	++m_uwaArgList.back();
}


void Program::increaseWaiID()
{
	++m_waiIDList.back();
}


void Program::increaseWaiArg()
{
	if (m_waiArgList.back() >= std::numeric_limits<char>::max())
		throw std::exception("Too big wai-arg.");

	++m_waiArgList.back();
}


std::size_t Program::getUwaID(std::size_t index) const
{
	return m_uwaIDList[index];
}


char Program::getUwaArg(std::size_t index) const
{
	return m_uwaArgList[index];
}


std::size_t Program::getWaiID(std::size_t index) const
{
	return m_waiIDList[index];
}


char Program::getWaiArg(std::size_t index) const
{
	return m_waiArgList[index];
}

//###################################################################################################

std::size_t Program::getStartIndex() const
{
	return m_beginIndex;
}


const std::vector<std::string>& Program::getCode() const
{
	return m_code;
}

