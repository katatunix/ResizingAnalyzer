#pragma once

#include <string>
#include "CompDecomp.h"

class Compressed : public CompDecomp
{
public:
	Compressed(Path& etcPackPath, Path& inputFilePath, Path& outputFolderPath) :
		CompDecomp(etcPackPath, inputFilePath, outputFolderPath) { }

protected:
	std::string options()
	{
		return "-c etc1";
	}

	std::string msg()
	{
		return "Could not compress the texture";
	}

	std::string ext()
	{
		return ".pkm";
	}
};
