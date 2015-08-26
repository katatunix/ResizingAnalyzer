#pragma once

#include <string>
#include "Resized.h"

class Double : public Resized
{
public:
	Double(Path& imageMagickPath, Path& inputFilePath, Path& outputFilePath) :
		Resized(imageMagickPath, inputFilePath, outputFilePath) { }

protected:
	std::string percent()
	{
		return "200%";
	}

	std::string msg()
	{
		return "Could not double the image";
	}
};
