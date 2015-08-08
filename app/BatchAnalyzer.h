#pragma once

#include "Paths.h"
#include "ImageAnalyzer.h"

#include <stdio.h>
#include <string>
#include <vector>

class BatchAnalyzer
{
public:
	BatchAnalyzer(Paths& inputPaths, ImageAnalyzer& imageAnalyzer)
		: m_inputPaths(inputPaths), m_imageAnalyzer(imageAnalyzer)
	{

	}

	std::string analyzeAndResize()
	{
		std::vector<std::string> files;
		std::vector<float> degrees;

		m_inputPaths.begin();
		while (m_inputPaths.hasNext())
		{
			std::string path = m_inputPaths.next();
			files.push_back(path);
			printf("Process image: %s", path.c_str());
			ImageAnalyzer::Result res = m_imageAnalyzer.resizableDegree(path, 0);
			printf("\t%.2f\n", res.degree);
			degrees.push_back(res.degree);
		}

		int count = files.size();
		for (int i = 0; i < count - 1; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (degrees[i] < degrees[j])
				{
					float tmpDeg = degrees[i];
					degrees[i] = degrees[j];
					degrees[j] = tmpDeg;

					std::string tmpFile = files[i];
					files[i] = files[j];
					files[j] = tmpFile;
				}
			}
		}

		std::string res = "";
		for (int i = 0; i < count; i++)
		{
			res += files[i] + "\t" + floatToString(degrees[i]) + "\n";
		}
		
		return res;
	}

private:
	std::string floatToString(float f)
	{
		char buffer[32];
		sprintf(buffer, "%.2f", f);
		return std::string(buffer);
	}

private:
	Paths& m_inputPaths;
	ImageAnalyzer& m_imageAnalyzer;
};
