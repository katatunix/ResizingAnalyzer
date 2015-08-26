#pragma once

#include <string>
#include <exception>
#include "Path.h"
#include "Half.h"
#include "Double.h"
#include "Compressed.h"
#include "Decompressed.h"
#include "Comparison.h"
#include "TgaImage.h"

class Analyzer
{
private:
	Path& m_imageMagickPath;
	Path& m_etcPackPath;
	int m_minSize;

public:
	Analyzer(Path& imageMagickPath, Path& etcPackPath, int minSize) :
		m_imageMagickPath(imageMagickPath),
		m_etcPackPath(etcPackPath),
		m_minSize(minSize)
	{
	}

	double analyze(Path& inputFilePath)
	{
		TgaImage originalImage(inputFilePath);
		if (originalImage.width() < m_minSize || originalImage.height() < m_minSize)
		{
			throw std::exception("The image size is too small to resize");
		}

		Path workingFolderPath(".\\" + inputFilePath.getFileNameWithoutExt() + "\\");
		Path halfFilePath(workingFolderPath.value() + "half.tga");
		Path doubleFilePath(workingFolderPath.value() + "double.tga");

		return Comparison(
			originalImage,

			TgaImage(
				Double(
					m_imageMagickPath,
					Decompressed(
						m_etcPackPath,
						Compressed(
							m_etcPackPath,
							Half(m_imageMagickPath, inputFilePath, halfFilePath),
							workingFolderPath
						),
						workingFolderPath
					),
					doubleFilePath
				)
			)
		).result();
	}

};
