#pragma once

#include <string>
#include <math.h>
#include "TgaImage.h"

class Comparison
{
public:
	Comparison(TgaImage& image1, TgaImage& image2) : m_image1(image1), m_image2(image2)
	{
	}

	double result()
	{
		if (m_image1.width() != m_image2.width() || m_image1.height() != m_image2.height()
			|| !m_image1.data() || !m_image2.data() || m_image1.hasAlpha() || m_image2.hasAlpha())
		{
			return -1.0;
		}

		int numPixels = m_image1.width() * m_image1.height();
		const char* p1 = m_image1.data();
		const char* p2 = m_image2.data();
		int channels1 = m_image1.numChannels();
		int channels2 = m_image2.numChannels();

		#define SQR(_x) ((_x) * (_x))

		// MSE = (1/N) sum (1/3) [ (R-R’)^2 + (G-G’)^2 +  (B-B’)^2]
		double mse = 0.0;
		for (int i = 0; i < numPixels; i++)
		{
			int j = i * channels1;
			int k = i * channels2;
			double r1, g1, b1, r2, g2, b2;

			if (channels1 == 1)
			{
				r1 = g1 = b1 = p1[j];
			}
			else
			{
				r1 = p1[j]; g1 = p1[j + 1]; b1 = p1[j + 2];
			}

			if (channels2 == 1)
			{
				r2 = g2 = b2 = p2[k];
			}
			else
			{
				r2 = p2[k]; g2 = p2[k + 1]; b2 = p2[k + 2];
			}

			mse += ( SQR(r1 - r2) + SQR(g1 - g2) + SQR(b1 - b2) ) / 3.0;
		}
		mse /= numPixels;

		// PSNR = 10 ln(255^2/MSE)/ln(10)
		return 10.0 * log(SQR(255.0) / mse) / log(10.0);
	}

private:

	TgaImage& m_image1;
	TgaImage& m_image2;
};
