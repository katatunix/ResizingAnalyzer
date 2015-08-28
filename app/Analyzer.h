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
#include "DosProcess.h"
#include "System.h"
#include "MainTga.h"
#include "AlphaTga.h"

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

		std::string imageName = inputFilePath.fileNameWithoutExt();

		Path workingFolderPath(System::currentFolder() + "\\" + imageName);
		if (DosProcess("md " + workingFolderPath.value()).execute() != 0)
		{
			throw std::exception("Could not create working folder");
		}

		if (!originalImage.hasAlpha())
		{
			return analyzeRgb(inputFilePath, originalImage, workingFolderPath);
		}
		
		return mymin(
			analyzeRgb(
				MainTga(originalImage, Path(workingFolderPath.value() + "\\" + imageName + "_main.tga")),
				workingFolderPath
			),
			analyzeRgb(
				AlphaTga(originalImage, Path(workingFolderPath.value() + "\\" + imageName + "_alpha.tga")),
				workingFolderPath
			)
		);
	}

private:
	double analyzeRgb(Path& inputFilePath, Path& workingFolderPath)
	{
		return analyzeRgb(inputFilePath, TgaImage(inputFilePath), workingFolderPath);
	}

	double analyzeRgb(Path& inputFilePath, TgaImage& tga, Path& workingFolderPath)
	{
		std::string imageName = inputFilePath.fileNameWithoutExt();
		Path halfFilePath(workingFolderPath.value() + "\\" + imageName + "_half.tga");
		Path doubleFilePath(workingFolderPath.value() + "\\" + imageName + "_double.tga");

		return Comparison(
			tga,

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

	double mymin(double x, double y)
	{
		return x < y ? x : y;
	}

};
