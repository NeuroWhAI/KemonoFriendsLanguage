#ifndef __KFL__TOKEN_H__
#define __KFL__TOKEN_H__


#include <vector>
#include <string>
#include <initializer_list>
#include <utility>




class Program;


class Token
{
public:
	Token(const std::initializer_list<std::string>& tokens);
	virtual ~Token() = default;


private:
	const std::vector<std::string> m_tokens;


public:
	bool check(const std::string& code) const;
	std::pair<bool, std::size_t> checkAndCompile(std::vector<std::string>::const_iterator itr,
		const std::string& code, Program& proc) const;


protected:
	virtual std::size_t compile(const std::vector<std::string>& tokens,
		std::vector<std::string>::const_iterator itr,
		const std::string& code, Program& proc) const = 0;
};


#endif