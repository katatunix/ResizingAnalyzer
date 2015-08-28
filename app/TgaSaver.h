#pragma once

#include <string>
#include <exception>
#include "tga/tga.h"

class TgaSaver
{
public:
	void save(int width, int height, int numChannels, unsigned char* data, const std::string& path)
	{
		tgaInfo* info = (tgaInfo*) malloc(sizeof(tgaInfo));
		info->width = width;
		info->height = height;
		info->pixelDepth = numChannels * 8;
		info->imageData = data;
		info->type = 2;
		info->status = TGA_OK;

		if (saveTga(info, path.c_str()) != 0)
		{
			throw std::exception(("Could not save the TGA to file: " + path).c_str());
		}
	}
};
