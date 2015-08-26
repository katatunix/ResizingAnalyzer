#pragma once

#include <string>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

class Process
{
private:
	std::string m_command;

public:
	Process(const std::string& command ) : m_command(command) { }

	int execute()
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		int len = m_command.length();

		WCHAR* wCommand = new WCHAR[len + 1];
		memset(wCommand, 0, sizeof(WCHAR) * (len + 1));
		mbstowcs(wCommand, m_command.c_str(), len);

		int exitCode;

		// Start the child process. 
		if (!CreateProcess(NULL,   // No module name (use command line)
			wCommand,        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi)           // Pointer to PROCESS_INFORMATION structure
			)
		{
			exitCode = -1;
		}
		else
		{
			// Wait until child process exits.
			WaitForSingleObject(pi.hProcess, INFINITE);

			DWORD e;
			GetExitCodeProcess(pi.hProcess, &e);
			exitCode = (int)e;

			// Close process and thread handles.
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}

		delete [] wCommand;
		return exitCode;
	}

};
