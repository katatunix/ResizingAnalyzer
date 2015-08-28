#include <stdio.h>
#include <conio.h>

#include "Path.h"
#include "Paths.h"
#include "BatchAnalyzer.h"

void usage()
{
	printf("Usage: ResizingAnalyzer.exe <ImageMagick Path> <etcpack Path> <input file/folder path> <min size>\n");
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
	Path inputPath(argv[3]);
	int minSize = atoi(argv[4]);

	BatchAnalyzer analyzer(imageMagickPath, etcPackPath, minSize);
	analyzer.analyze(Paths(inputPath));

	printf("\n\nPress any key to exit...\n");
	_getch();

	return 0;
}
