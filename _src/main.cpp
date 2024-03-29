// lab1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "memory.h"
#include "time.h"

#include "omp.h"

#include <IL/ilut.h>
#include <IL/ilu.h>

#include "emmintrin.h"
#include "nmmintrin.h"

#include "defs.h"
#include "func.h"



void main()
{

	//LOADING IMAGE
	//---------------------------------------------------------------------------------------
	printf("start\n");

	ilInit(); iluInit();
	ILboolean ret;
	ILuint ilImg = 0;
	ilGenImages(1, &ilImg);
	ilBindImage(ilImg);
	ret = ilLoadImage((const char*)("input.jpg"));
	ILubyte* imgData = ilGetData();

	int imgWidth = ilGetInteger(IL_IMAGE_WIDTH);
	int imgHeight = ilGetInteger(IL_IMAGE_HEIGHT);
	ILint imgOrigin = ilGetInteger(IL_ORIGIN_MODE);

	printf("Input resolution: %4dx%4d\n", imgWidth, imgHeight);

	unsigned char *imgSrcExt;
	int imgWidthF = imgWidth + FILTER_SIZE - 1;
	int imgHeightF = imgHeight + FILTER_SIZE - 1;
	int imgFOfssetW =  (FILTER_SIZE -1)/2;
	int imgFOfssetH = (FILTER_SIZE - 1) / 2;
	imgSrcExt = (unsigned char *)(_aligned_malloc(3 * imgWidthF*imgHeightF * sizeof(unsigned char), 32));
	int row, col;

	for (row = 0; row < imgHeightF; row++)
	{
		for (col = 0; col < imgWidthF;col++)
		{
			int pixel = (row*imgWidthF + col) * 3;
			*(imgSrcExt + pixel + 0) = 0;
			*(imgSrcExt + pixel + 1) = 0;
			*(imgSrcExt + pixel + 2) = 0;
		}
	}

	for (row = 0; row < imgHeight; row++)
	{
		for (col = 0; col < imgWidth;col++)
		{
			int pixel_dst = ((row + imgFOfssetH)*imgWidthF + (col + imgFOfssetW)) * 3;
			int pixel_src = (row*imgWidth + col) * 3;
			*(imgSrcExt + pixel_dst + 0) = (unsigned char)(*(imgData + pixel_src + 0));
			*(imgSrcExt + pixel_dst + 1) = (unsigned char)(*(imgData + pixel_src + 1));
			*(imgSrcExt + pixel_dst + 2) = (unsigned char)(*(imgData + pixel_src + 2));
		}
	}

	unsigned char *imgRes;
	imgRes = (unsigned char *)(_aligned_malloc(3 * imgWidth*imgHeight * sizeof(unsigned char), 32));

	// IMAGE PROCESSING
	//---------------------------------------------------------------------------------------
	clock_t s0, e0;
	double d0;
	double mpixel;

	printf("Start Median Filtering\n");
	s0 = clock();
	for (int r = 0; r < RUNS; r++)
	{
		img_filter(imgHeight, imgWidth, imgWidthF, imgSrcExt, imgRes);
		printf("%d\n", r);
	}

	e0 = clock();
	d0 = (double)(e0 - s0) / (RUNS*CLOCKS_PER_SEC);
	mpixel = (imgWidth*imgHeight / d0) / 1000000;
	printf("C CPU TIME: %4.4f\n", d0);
	printf("C Mpixel/s: %4.4f\n", mpixel);


	//---------------------------------------------------------------------------------------
	// IMAGE PROCESSING END

	for (row = 0; row < imgHeight; row++)
	{
		for (col = 0; col < imgWidth;col++)
		{
			int pixel_src = (row*imgWidth + col) * 3;
			int pixel_dst = (row*imgWidth + col) * 3;
			*(imgData + pixel_dst + 0) = (ILubyte)(*(imgRes + pixel_src + 0));
			*(imgData + pixel_dst + 1) = (ILubyte)(*(imgRes + pixel_src + 1));
			*(imgData + pixel_dst + 2) = (ILubyte)(*(imgRes + pixel_src + 2));
		}
	}

	_aligned_free(imgSrcExt);
	_aligned_free(imgRes);

	ret = ilSetData(imgData);
	ilEnable(IL_FILE_OVERWRITE);
	ilSaveImage((const char*)("output.bmp"));
	ilDeleteImages(1, &ilImg);
}



//FILTER TEST
/*
int main(void) {
	int result;


	int matrix[5][5]=
	{
		{0,0,0,0,0},
		{0,0,0,0,0},
		{134,122,122,123,120},
		{132,120,121,122,119},
		{132,120,121,121,119}
	};

	int tp[5][5] =
	{
		{0,0,0,0,0},
		{0,0,0,0,0},
		{134,122,122,123,120},
		{132,120,121,122,119},
		{132,120,121,121,119}
	};

	result = median_filter(matrix);
	printf("\nresult= %d\n\n",result);

	result = median_filter_ref(tp);
	printf("ref= %d\n\n", result);



	return 0;
}
*/