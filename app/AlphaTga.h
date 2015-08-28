#pragma once

#include <string>
#include <exception>
#include "Path.h"

class AlphaTga : public Path
{
public:
	AlphaTga(TgaImage& originalTga, Path& outputFilePath)
		: m_originalTga(originalTga), m_outputFilePath(outputFilePath) { }

	virtual const std::string& value()
	{
		const char* original = m_originalTga.data();
		int w = m_originalTga.width();
		int h = m_originalTga.height();
		int num = m_originalTga.numChannels();

		char* mainData = new char[w * h * 3];
		int i = 0, j = 0;
		while (i < w * h * num)
		{
			mainData[j++] = original[i + 3];
			mainData[j++] = original[i + 3];
			mainData[j++] = original[i + 3];
			i += num;
		}

		m_value = m_outputFilePath.value();
		TgaSaver().save(w, h, 3, (unsigned char*)mainData, m_value);

		delete [] mainData;

		return m_value;
	}

private:
	TgaImage& m_originalTga;
	Path& m_outputFilePath;
};
