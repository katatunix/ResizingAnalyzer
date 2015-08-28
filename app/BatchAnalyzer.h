#pragma once

#include "Analyzer.h"
#include "Paths.h"
#include <vector>

class BatchAnalyzer
{
private:
	Path& m_imageMagickPath;
	Path& m_etcPackPath;
	int m_minSize;
	Analyzer m_analyzer;

public:
	BatchAnalyzer(Path& imageMagickPath, Path& etcPackPath, int minSize) :
		m_imageMagickPath(imageMagickPath),
		m_etcPackPath(etcPackPath),
		m_minSize(minSize),
		m_analyzer(imageMagickPath, etcPackPath, minSize)
	{
	}

	void analyze(Paths& paths)
	{
		std::vector<std::string> pathValues;
		std::vector<double> diffs;
		while (paths.hasNext())
		{
			Path& path = paths.next();
			double diff;
			try
			{
				diff = m_analyzer.analyze(path);
			}
			catch (std::exception&)
			{
				diff = -1.0;
			}
			diffs.push_back(diff);
			pathValues.push_back(path.value());
		}

		int len = diffs.size();
		for (int i = 0; i < len - 1; i++)
		{
			for (int j = i + 1; j < len; j++)
			{
				if (diffs[i] > diffs[j])
				{
					double tmpDiff = diffs[i];
					diffs[i] = diffs[j];
					diffs[j] = tmpDiff;
					std::string tmpPath = pathValues[i];
					pathValues[i] = pathValues[j];
					pathValues[j] = tmpPath;
				}
			}
		}

		printf("\n\n================================================================\n");
		printf("REPORT\n");
		printf("================================================================\n");

		for (int i = 0; i < len; i++)
		{
			printf("[%.2f] %s\n", diffs[i], pathValues[i].c_str());
		}
	}
};
