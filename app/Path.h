#pragma once

#include <string>

class Path
{
public:
	Path(const std::string& value) : m_value(value) { }

	virtual const std::string& value()
	{
		return m_value;
	}

	std::string getFileNameWithoutExt()
	{
		std::size_t idx = m_value.find_last_of('\\');
		if (idx == std::string::npos)
		{
			return m_value;
		}

		std::string fileName = m_value.substr(idx + 1);
		idx = fileName.find_last_of('.');
		if (idx == std::string::npos)
		{
			return fileName;
		}

		return fileName.substr(0, idx);
	}

protected:
	std::string m_value;
};
