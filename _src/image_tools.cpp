#include "func.h"
#include <stdio.h>

void img_filter(int imgHeight, int imgWidth, int imgWidthF, unsigned char *imgSrcExt, unsigned char *imgDst)
{
	int wr_base;				//pixel specific address for writing the results to the output
	int rd_base;				//pixel specific address for reading the values from the input
	int window_offset;			//address offset for traversing in the filtering window
	int ch_result[3];			//color channels filtered value

								//matrices that collects a color channel's data so it can be feeded to the filter
	int R[FILTER_SIZE][FILTER_SIZE];
	int G[FILTER_SIZE][FILTER_SIZE];
	int B[FILTER_SIZE][FILTER_SIZE];


	//traversing trough the image
	for (int row = 0; row < imgHeight; row++)
	{
		//base addresses for "pixels", both for read and write scenario
		wr_base = row*imgWidth * 3;
		rd_base = row*imgWidthF * 3;


		for (int col = 0; col < imgWidth; col++)
		{
			window_offset = 0;

			for (int fy = 0 ; fy < (FILTER_SIZE ) ; fy++)
			{
				for (int fx = 0; fx < (FILTER_SIZE ) ; fx++)
				{
					//creating matrices for every channel so we can filter them 
					R[fy][fx] = (short)(*(imgSrcExt + rd_base + window_offset + 0));
					G[fy][fx] = (short)(*(imgSrcExt + rd_base + window_offset + 1));
					B[fy][fx] = (short)(*(imgSrcExt + rd_base + window_offset + 2));

					window_offset = window_offset + 3;
				}
				window_offset = window_offset - 5 * 3 + imgWidthF * 3;
			}

			//filtering
			ch_result[0] = median_filter_ref(R);
			ch_result[1] = median_filter_ref(G);
			ch_result[2] = median_filter_ref(B);

			//saveing results
			*(imgDst + wr_base + 0) = (unsigned char)(ch_result[0]);
			*(imgDst + wr_base + 1) = (unsigned char)(ch_result[1]);
			*(imgDst + wr_base + 2) = (unsigned char)(ch_result[2]);


			//shifting over to the next pixel
			wr_base = wr_base + 3;
			rd_base = rd_base + 3;
		}
		//stepping over the padding
		wr_base = wr_base + 4 * 3;
		rd_base = rd_base + 4 * 3;
	}
}

void img_read_write_test(int imgHeight, int imgWidth, int imgWidthF, unsigned char *imgSrcExt, unsigned char *imgDst)
{
	int wr_base;				//pixel specific address for writing the results to the output
	int rd_base;				//pixel specific address for reading the values from the input
	int ch_result[3];			//color channels filtered value



								//traversing trough the image
	for (int row = 0; row < imgHeight; row++)
	{
		//base addresses for "pixels", both for read and write scenario
		wr_base = row*imgWidth * 3;
		rd_base = row*imgWidthF * 3;


		for (int col = 0; col < imgWidth; col++)
		{

			//creating matrices for every channel so we can filter them 
			ch_result[0] = (short)(*(imgSrcExt + rd_base + 0));
			ch_result[1] = (short)(*(imgSrcExt + rd_base + 1));
			ch_result[2] = (short)(*(imgSrcExt + rd_base + 2));


			//filtering

			//saveing results
			*(imgDst + wr_base + 0) = (unsigned char)(ch_result[0]);
			*(imgDst + wr_base + 1) = (unsigned char)(ch_result[1]);
			*(imgDst + wr_base + 2) = (unsigned char)(ch_result[2]);


			//shifting over to the enxt pixel
			wr_base = wr_base + 3;
			rd_base = rd_base + 3;
		}
		//stepping over the padding
		wr_base = wr_base + 4 * 3;
		rd_base = rd_base + 4 * 3;
	}
}

void img_filter_test(int imgHeight, int imgWidth, int imgWidthF, unsigned char *imgSrcExt, unsigned char *imgDst)
{
	int wr_base;				//pixel specific address for writing the results to the output
	int rd_base;				//pixel specific address for reading the values from the input
	int window_offset;			//address offset for traversing in the filtering window
	int ch_result[3];			//color channels filtered value

								//matrices that collects a color channel's data so it can be feeded to the filter
	int R[FILTER_SIZE][FILTER_SIZE];
	int G[FILTER_SIZE][FILTER_SIZE];
	int B[FILTER_SIZE][FILTER_SIZE];

	int E[FILTER_SIZE][FILTER_SIZE];

	int error_cnt = 0;
	bool error = false;

	//traversing trough the image
	for (int row = 0; row < imgHeight; row++)
	{
		//base addresses for "pixels", both for read and write scenario
		wr_base = row*imgWidth * 3;
		rd_base = row*imgWidthF * 3;


		for (int col = 0; col < imgWidth; col++)
		{
			window_offset = 0;

			for (int fy = 0; fy < (FILTER_SIZE); fy++)
			{
				for (int fx = 0; fx < (FILTER_SIZE); fx++)
				{
					//creating matrices for every channel so we can filter them 
					R[fy][fx] = (short)(*(imgSrcExt + rd_base + window_offset + 0));
					E[fy][fx] = (short)(*(imgSrcExt + rd_base + window_offset + 0));
					G[fy][fx] = (short)(*(imgSrcExt + rd_base + window_offset + 1));
					B[fy][fx] = (short)(*(imgSrcExt + rd_base + window_offset + 2));

					window_offset = window_offset + 3;
				}
				window_offset = window_offset - 5 * 3 + imgWidthF * 3;
			}

			//filtering
			ch_result[0] = median_filter_ref(R);
			ch_result[1] = median_filter_ref(G);
			ch_result[2] = median_filter_ref(B);

			//detect errors in filtering:
			if (median_filter(R) != ch_result[0] && !error) { 
				printf("\nError in matrix:\n");
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						printf("%d\t",E[i][j]);
					}
					printf("\n");
				}

				printf("ref=%d error=%d\n", ch_result[0], median_filter(R));

				error_cnt++;
				error = true;
				//printf("ERROR:pos:%d row:%d col:%d", rd_base, rd_base%imgWidthF,rd_base-rd_base%imgWidthF*imgWidthF);
			}

			//saveing results
			*(imgDst + wr_base + 0) = (unsigned char)(ch_result[0]);
			*(imgDst + wr_base + 1) = (unsigned char)(ch_result[1]);
			*(imgDst + wr_base + 2) = (unsigned char)(ch_result[2]);


			//shifting over to the next pixel
			wr_base = wr_base + 3;
			rd_base = rd_base + 3;
		}
		//stepping over the padding
		wr_base = wr_base + 4 * 3;
		rd_base = rd_base + 4 * 3;
	}

	printf("ERROR COUNTER:%d", error_cnt);
}