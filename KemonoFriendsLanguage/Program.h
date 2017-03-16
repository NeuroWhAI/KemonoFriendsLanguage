#ifndef __KFL__PROGRAM_H__
#define __KFL__PROGRAM_H__


#include <vector>
#include <string>




class Program
{
public:
	static const int TYPE_TO_CHAR = 32;
	enum class Types : int
	{
		NOP = 0,
		STR,
		NUM,
		FUNC,
		CALL,
		TAN,
		SUG,
		UWA,
		WAI,
		NANI,
		OMOS,
		LAL,
		MYA,
		SARU,
		SABT,

		//----------------------------
		Count
	};


public:
	Program();


private:
	std::size_t m_beginIndex;
	std::vector<std::string> m_code;
	std::vector<std::size_t> m_uwaIDList;
	std::vector<char> m_uwaArgList;
	std::vector<std::size_t> m_waiIDList;
	std::vector<char> m_waiArgList;


public:
	void setMain(std::size_t index);
	void pushCall(std::size_t destIndex);
	void pushCmd(Types type);
	void pushCmd(Types type, const std::string& arg);


public:
	void appendUwaiList();
	void increaseUwaID();
	void increaseUwaArg();
	void increaseWaiID();
	void increaseWaiArg();
	std::size_t getUwaID(std::size_t index) const;
	char getUwaArg(std::size_t index) const;
	std::size_t getWaiID(std::size_t index) const;
	char getWaiArg(std::size_t index) const;


public:
	std::size_t getStartIndex() const;
	const std::vector<std::string>& getCode() const;
};


#endif