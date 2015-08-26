#pragma once

#include <string>
#include "Path.h"

class Decompressed : public Path
{
public:
	Decompressed(Path& etcPackPath, Path& inputFilePath, Path& outputFolderPath)
	{
	}

	virtual const std::string& value()
	{
		// TODO
		return m_value;
	}
};
