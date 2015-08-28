#pragma once

#include <string>
#include <windows.h>
#include <stdio.h>

#include "Process.h"

class DosProcess : public Process
{
public:
	DosProcess(const std::string& command ) : Process(command) { }

	int execute()
	{
		FILE* pipe = _popen(m_command.c_str(), "r");
		if (!pipe)
		{
			return 1;
		}

		const int max = 1024;
		char buffer[max];
		std::string result = "";
		while (!feof(pipe))
		{
			if (fgets(buffer, max, pipe))
			{
				result += buffer;
			}
		}
		_pclose(pipe);
		printf("%s\n", result.c_str());
		return 0;
	}

};
