#pragma once

#include <string>

class TgaImage
{
public:
	TgaImage(Path& tgaFilePath)
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
		3 or 4 or 0
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
