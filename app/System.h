#pragma once

#include <string>
#include <stdio.h>
#include <windows.h>

class System
{
public:
	static std::string currentFolder()
	{
		const int MAX = 1024;
		wchar_t buf [MAX];
		GetCurrentDirectory(MAX, buf);

		std::wstring tmp = buf;
		return convert(tmp);
	}

	static std::string convert(const std::wstring& ws)
	{
		std::string result;
		for (WCHAR x : ws)
		{
			result += (char)x;
		}
		return result;
	}

	static std::wstring convert(const std::string& s)
	{
		std::wstring result;
		for (char x : s)
		{
			result += x;
		}
		return result;
	}
};
