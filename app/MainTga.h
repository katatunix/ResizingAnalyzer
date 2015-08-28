#pragma once

#include <string>
#include "Path.h"
#include "TgaImage.h"
#include "TgaSaver.h"

class MainTga : public Path
{
public:
	MainTga(TgaImage& originalTga, Path& outputFilePath)
		: m_originalTga(originalTga), m_outputFilePath(outputFilePath) { }

	const std::string& value()
	{
		const char* original = m_originalTga.data();
		int w = m_originalTga.width();
		int h = m_originalTga.height();
		int num = m_originalTga.numChannels();

		char* mainData = new char[w * h * 3];
		int i = 0, j = 0;
		while (i < w * h * num)
		{
			memcpy(mainData + j, original + i, 3);
			i += num;
			j += 3;
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
