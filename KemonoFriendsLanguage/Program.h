#ifndef __KFL__PROGRAM_H__
#define __KFL__PROGRAM_H__


#include <vector>
#include <string>




class Program
{
public:
	static const std::string NOP;
	static const std::string FUNC;
	static const std::string CALL;
	static const std::string CMD;
	static const std::string TAN;
	static const std::string SUG;
	static const std::string UWA;
	static const std::string WAI;
	static const std::string NANI;
	static const std::string OMOS;
	static const std::string LAL;
	static const std::string SARU;
	static const std::string SABT;


public:
	Program();


private:
	std::size_t m_beginIndex;
	std::vector<std::string> m_code;


public:
	void setMain(std::size_t index);
	void pushNop();
	void pushFunc();
	void pushCall(std::size_t destIndex);
	void pushCmd(const std::string& cmd);
	void pushCmd(const std::string& subType, const std::string& cmd);


public:
	std::size_t getStartIndex() const;
	const std::vector<std::string>& getCode() const;
};


#endif