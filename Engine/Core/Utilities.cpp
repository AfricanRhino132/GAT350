#include "Utilities.h" 
#include <algorithm> 
#include <iostream>

namespace neu
{
	std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		
		std::transform(str.begin(), str.end(), lower.begin(), ::tolower);

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper = str;
		
		std::transform(str.begin(), str.end(), upper.begin(), ::toupper);

		return upper;
	}

	bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
	{
		if (str1.size() != str2.size())
		{
			return false;
		}

		std::string lower1 = ToLower(str1);
		std::string lower2 = ToLower(str2);

		return lower1 == lower2;
	}
}