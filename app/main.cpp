#include <stdio.h>
#include <conio.h>
#include <exception>

#include "Path.h"
#include "Analyzer.h"

void usage()
{
	printf("Usage: ResizingAnalyzer.exe <ImageMagick Path> <etcpack Path> <TGA file path> <min size>\n");
}

int main(int argc, const char *argv[])
{
	if (argc != 5)
	{
		usage();
		return 1;
	}

	Path imageMagickPath(argv[1]);
	Path etcPackPath(argv[2]);
	Path inputFilePath(argv[3]);
	int minSize = atoi(argv[4]);

	Analyzer analyzer(imageMagickPath, etcPackPath, minSize);
	int exitCode = 0;
	try
	{
		double res = analyzer.analyze(inputFilePath);
		printf("Result: %.2f\n", res);
	}
	catch (std::exception& ex)
	{
		printf("Error: %s\n", ex.what());
		exitCode = 1;
	}
	
	return exitCode;
}
