#pragma once

#include <string>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <exception>

class Process
{
protected:
	std::string m_command;
	std::string m_workingDir;

public:
	Process(const std::string& command, const std::string& workingDir) :
		m_command(command), m_workingDir(workingDir) { }
	
	Process(const std::string& command) : Process(command, "") { }

	virtual int execute()
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		int len = m_command.length();

		WCHAR* wCommand = new WCHAR[len + 1];
		mbstowcs(wCommand, m_command.c_str(), len);
		wCommand[len] = 0;

		WCHAR* wWorkingDir = 0;
		len = m_workingDir.length();
		if (len > 0)
		{
			wWorkingDir = new WCHAR[len + 1];
			mbstowcs(wWorkingDir, m_workingDir.c_str(), len);
			wWorkingDir[len] = 0;
		}

		int exitCode;

		// Start the child process. 
		if (!CreateProcess(NULL,   // No module name (use command line)
			wCommand,        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			wWorkingDir,    // starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi)           // Pointer to PROCESS_INFORMATION structure
			)
		{
			exitCode = -1;
			std::string msg = "Could not execute the command: " + m_command;
			throw std::exception(msg.c_str());
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
		if (wWorkingDir) delete [] wWorkingDir;
		return exitCode;
	}

};
