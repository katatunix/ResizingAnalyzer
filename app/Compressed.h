#pragma once

#include <string>
#include "Path.h"

class Compressed : public Path
{
public:
	Compressed(Path& etcPackPath, Path& inputFilePath, Path& outputFolderPath)
	{
	}

	virtual const std::string& value()
	{
		// TODO
		return m_value;
	}
};
