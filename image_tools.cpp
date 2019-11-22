#include "func.h"

void extract_data(int imgHeight, int imgWidth, int imgWidthF, unsigned char *imgSrcExt, unsigned char *imgDst)
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

			for (int fy = -(FILTER_SIZE - 1) / 2; fy < (FILTER_SIZE - 1) / 2; fy++)
			{
				for (int fx = -(FILTER_SIZE - 1) / 2; fx < (FILTER_SIZE - 1) / 2; fx++)
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
			ch_result[0] = medianFilter(R);
			ch_result[1] = medianFilter(G);
			ch_result[2] = medianFilter(B);

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