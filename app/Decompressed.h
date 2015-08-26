#pragma once

#include <string>
#include "CompDecomp.h"

class Decompressed : public CompDecomp
{
public:
	Decompressed(Path& etcPackPath, Path& inputFilePath, Path& outputFolderPath) :
		CompDecomp(etcPackPath, inputFilePath, outputFolderPath) { }

protected:
	std::string options()
	{
		return "-ext TGA";
	}

	std::string msg()
	{
		return "Could not decompress the texture";
	}

	std::string ext()
	{
		return ".tga";
	}
};
