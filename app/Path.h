#pragma once

#include <string>
#include <windows.h>
#include "System.h"

class Path
{
public:
	Path(const std::string& value) : m_value(value) { }
	Path() : Path("") { }

	virtual const std::string& value()
	{
		return m_value;
	}

	std::string fileNameWithoutExt()
	{
		std::size_t idx = findLastSlash(m_value);
		std::string fileName = idx == std::string::npos ? m_value : m_value.substr(idx + 1);

		idx = fileName.find_last_of('.');
		return idx == std::string::npos ? fileName : fileName.substr(0, idx);
	}

	std::string folderPath()
	{
		std::size_t idx = findLastSlash(m_value);
		return idx == std::string::npos ? "" : m_value.substr(0, idx);
	}

	bool isFolder()
	{
		return GetFileAttributes(System::convert(m_value).c_str()) & FILE_ATTRIBUTE_DIRECTORY;
	}

private:
	std::size_t findLastSlash(const std::string str)
	{
		std::size_t idx1 = m_value.find_last_of('\\');
		std::size_t idx2 = m_value.find_last_of('/');
		if (idx1 == std::string::npos) return idx2;
		if (idx2 == std::string::npos) return idx1;
		return idx1 > idx2 ? idx1 : idx2;
	}

protected:
	std::string m_value;
};
