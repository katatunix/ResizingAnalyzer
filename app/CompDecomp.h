#pragma once

#include <string>
#include "Path.h"
#include "Process.h"

class CompDecomp : public Path
{
public:
	CompDecomp(Path& etcPackPath, Path& inputFilePath, Path& outputFolderPath) :
		m_etcPackPath(etcPackPath),
		m_inputFilePath(inputFilePath),
		m_outputFolderPath(outputFolderPath) { }

	virtual const std::string& value()
	{
		if (Process(
			m_etcPackPath.value() + " " + m_inputFilePath.value() + " " + m_outputFolderPath.value()
				+ " " + options()
			).execute() != 0)
		{
			throw std::exception(msg().c_str());
		}
		return m_value = m_outputFolderPath.value() + m_inputFilePath.getFileNameWithoutExt() + ext();
	}

protected:
	virtual std::string options() = 0;
	virtual std::string msg() = 0;
	virtual std::string ext() = 0;

private:
	Path& m_etcPackPath;
	Path& m_inputFilePath;
	Path& m_outputFolderPath;
};
