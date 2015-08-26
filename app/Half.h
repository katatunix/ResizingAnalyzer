#pragma once

#include <string>
#include "Resized.h"

class Half : public Resized
{
public:
	Half(Path& imageMagickPath, Path& inputFilePath, Path& outputFilePath) :
		Resized(imageMagickPath, inputFilePath, outputFilePath) { }

protected:
	std::string percent()
	{
		return "50%";
	}

	std::string msg()
	{
		return "Could not half the image";
	}
};
