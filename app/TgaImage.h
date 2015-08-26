#pragma once

#include "Path.h"
#include "tga/tga.h"

class TgaImage
{
public:
	TgaImage(Path& tgaFilePath)
	{
	}

	~TgaImage()
	{
	}

	int width()
	{
		return 0;
	}

	int height()
	{
		return 0;
	}

	/*
		3 or 4
	*/
	int numChannels()
	{
		return 3;
	}

	const char* data()
	{
		return 0;
	}

};
