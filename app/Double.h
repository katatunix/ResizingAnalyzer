#pragma once

#include <string>
#include "Path.h"

class Double : public Path
{
public:
	Double(Path& imageMagickPath, Path& inputFilePath, Path& outputFilePath) : Path("")
	{
	}

	virtual const std::string& value()
	{
		// TODO
		return m_value;
	}
};
