#pragma once

#include <string>
#include <vector>
#include <exception>

#include <stdio.h>
#include <windows.h>

#include "Path.h"
#include "System.h"

class Paths
{
private:
	std::vector<Path> m_list;
	unsigned int m_idx;

public:
	Paths(Path& rootPath)
	{
		if (rootPath.isFolder())
		{
			WIN32_FIND_DATA ffd;
			HANDLE hFind = INVALID_HANDLE_VALUE;
			std::wstring ws = System::convert(rootPath.value());
			hFind = FindFirstFile(System::convert(rootPath.value() + "\\*.tga").c_str(), &ffd);
			if (INVALID_HANDLE_VALUE == hFind)
			{
				throw std::exception(("Could not get file list of the folder: " + rootPath.value()).c_str());
			}
			do
			{
				if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					m_list.push_back(
						Path(
							rootPath.value() + "\\" + System::convert(ffd.cFileName)
						)
					);
				}
			}
			while (FindNextFile(hFind, &ffd) != 0);
			FindClose(hFind);
		}
		else
		{
			m_list.push_back(rootPath);
		}
		m_idx = 0;
	}

	bool hasNext()
	{
		return m_idx < m_list.size();
	}

	Path& next()
	{
		if (!hasNext())
		{
			throw std::exception("No element");
		}
		return m_list[m_idx++];
	}
};
