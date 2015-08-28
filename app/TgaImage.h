#pragma once

#include "Path.h"
#include "tga/tga.h"
#include <exception>

class TgaImage
{
private:
	tgaInfo* m_info;

public:
	TgaImage(Path& tgaFilePath)
	{
		m_info = tgaLoad(tgaFilePath.value().c_str());
		if (m_info->status != TGA_OK)
		{
			tgaDestroy(m_info);
			throw std::exception("Could not load the TGA file");
		}
	}

	~TgaImage()
	{
		tgaDestroy(m_info);
	}

	int width()
	{
		return m_info->width;
	}

	int height()
	{
		return m_info->height;
	}

	/*
		3 or 4
	*/
	bool hasAlpha()
	{
		return m_info->pixelDepth == 32;
	}

	int numChannels()
	{
		return m_info->pixelDepth / 8;
	}

	const char* data()
	{
		return (const char*)m_info->imageData;
	}
};
