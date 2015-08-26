#pragma once

#include <string>
#include "Path.h"

class Half : public Path
{
public:
	Half(Path& imageMagickPath, Path& inputFilePath, Path& outputFilePath)
	{
	}

	virtual const std::string& value()
	{
		// TODO
		return m_value;
	}
};
