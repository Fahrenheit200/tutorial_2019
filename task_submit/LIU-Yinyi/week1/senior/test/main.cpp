#include "MaxCommonSuffix.hpp"

int main()
{
	std::vector<std::string> test1 { "ppp", "pplpp", "lpp" };
	
	std::cout << longestCommon(test1) << std::endl;
	return 0;
}
