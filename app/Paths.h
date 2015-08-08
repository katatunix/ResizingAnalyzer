#pragma once

#include <stdio.h>
#include <string>

class Paths
{
public:
	Paths(const std::string& txtFilePath) : m_file(NULL), m_txtFilePath(txtFilePath)
	{
	}

	virtual ~Paths()
	{
		close();
	}

	void begin()
	{
		close();
		m_file = fopen(m_txtFilePath.c_str(), "rt");
	}

	bool hasNext()
	{
		return m_file && !feof(m_file);
	}

	std::string next()
	{
		const int MAX = 1024;
		char buffer[MAX];
		fgets(buffer, MAX, m_file);

		int lastIndex = strlen(buffer) - 1;
		if (lastIndex >= 0 && buffer[lastIndex] == '\n')
		{
			buffer[lastIndex] = 0;
		}

		return std::string(buffer);
	}

private:
	void close()
	{
		if (m_file)
		{
			fclose(m_file);
			m_file = NULL;
		}
	}

private:
	FILE* m_file;
	std::string m_txtFilePath;
};
