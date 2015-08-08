#pragma once

#include <string>
#include "tga.h"

class ImageAnalyzer
{
private:
	typedef unsigned char u8;

public:
	struct Result
	{
		bool shouldBeResized;
		float degree;
	};

	Result resizableDegree(const std::string& path, int minSize)
	{
		Result res;
		res.shouldBeResized = false;
		res.degree = -1.f;

		tgaInfo* info = tgaLoad(path.c_str());
		if (info->status != TGA_OK)
		{
			goto my_end;
		}

		short& width = info->width;
		short& height = info->height;
		if (width % 2 == 1 || height % 2 == 1 || width < minSize || height < minSize)
		{
			goto my_end;
		}

		const int numComponents = info->pixelDepth / 8;
		u8* p = info->imageData;

		float* deltas = new float[width * height / 4];
		int numPixels = 0;
		short row = 0, col = 0;
		while (row < height)
		{
			while (col < width)
			{
				int offset1 = (row * width + col) * numComponents;
				int offset2 = (row * width + col + 1) * numComponents;
				int offset3 = ((row + 1) * width + col + 1) * numComponents;
				int offset4 = ((row + 1) * width + col) * numComponents;

				float avgPixel[4];
				for (int i = 0; i < numComponents; i++)
				{
					avgPixel[i] = (p[offset1 + i] + p[offset2 + i] + p[offset3 + i] + p[offset4 + i]) / 4.f;
				}

				deltas[numPixels++] = pixelDelta(p + offset1, avgPixel, numComponents)
					+ pixelDelta(p + offset2, avgPixel, numComponents)
					+ pixelDelta(p + offset3, avgPixel, numComponents)
					+ pixelDelta(p + offset4, avgPixel, numComponents);

				//----------------------------------------------------------------
				col += 2;
			}

			row += 2;
		}

		float sum = 0.f;
		for (int i = 0; i < numPixels; i++)
		{
			sum += deltas[i];
		}

		delete [] deltas;
		res.degree = sum / numPixels;
		res.shouldBeResized = true;

	my_end:
		tgaDestroy(info);
		return res;
	}

private:
	float pixelDelta(u8* p1, float* p2, int comp)
	{
		float d = 0.f;
		for (int i = 0; i < comp; i++)
		{
			d += abs((float)p1[i], p2[i]);
		}
		return d;
	}

	float abs(float x, float y)
	{
		return x > y ? x - y : y - x;
	}
};
