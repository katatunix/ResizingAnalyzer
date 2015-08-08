#include <stdio.h>
#include <conio.h>

#include "ImageAnalyzer.h"
//#include "BatchAnalyzer.h"
//#include "Paths.h"

void usage()
{
	printf("Usage: ResizingAnalyzer.exe <file> <threshold> <minSize>\n");
}

int main(int argc, const char *argv[])
{
	if (argc < 4)
	{
		usage();
		return 0;
	}

	const char* file = argv[1];
	float threshold = (float)atof(argv[2]);
	int minSize = atoi(argv[3]);

	ImageAnalyzer imageAnalyzer;
	ImageAnalyzer::Result res = imageAnalyzer.resizableDegree(file, minSize);

	if (!res.shouldBeResized) return -1;
	return res.degree <= threshold ? 0 : 1;
}
