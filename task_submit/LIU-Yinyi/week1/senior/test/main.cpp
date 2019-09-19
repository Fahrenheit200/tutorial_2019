#include "MaxCommonSuffix.hpp"

int main()
{
	std::vector<std::string> test1 { "ppp", "pplpp", "lpp" };
	std::vector<std::string> test2 { "", "" };
	std::vector<std::string> test3 { "c", "c" };
	std::vector<std::string> test4 { "dc3v9djfe", "cavj38feifjfe" };
	
	std::cout << longestCommon(test1) << std::endl;
	std::cout << longestCommon(test2) << std::endl;
	std::cout << longestCommon(test3) << std::endl;
	std::cout << longestCommon(test4) << std::endl;
	return 0;
}
