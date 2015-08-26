#pragma once

#include <string>
#include "Path.h"
#include "Process.h"

class Resized : public Path
{
public:
	Resized(Path& imageMagickPath, Path& inputFilePath, Path& outputFilePath) :
		m_imageMagickPath(imageMagickPath),
		m_inputFilePath(inputFilePath),
		m_outputFilePath(outputFilePath) { }

	virtual const std::string& value()
	{
		if (Process(
			m_imageMagickPath.value() + " " + m_inputFilePath.value()
				+ " -resize " + percent() + " " + m_outputFilePath.value()
			).execute() != 0)
		{
			throw std::exception(msg().c_str());
		}
		return m_value = m_outputFilePath.value();
	}

protected:
	virtual std::string percent() = 0;
	virtual std::string msg() = 0;

private:
	Path& m_imageMagickPath;
	Path& m_inputFilePath;
	Path& m_outputFilePath;
};
