#include "func.h"
#include "defs.h"
#include <stdio.h>
#include <algorithm>
using namespace std;

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

			for (int fy = -(FILTER_SIZE-1)/2; fy <  (FILTER_SIZE - 1) / 2; fy++)
			{
				for (int fx = -(FILTER_SIZE - 1) / 2; fx <  (FILTER_SIZE - 1) / 2; fx++)
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

int medianFilter(int matrix[FILTER_SIZE][FILTER_SIZE])
{
	int result = 0;
	int temp[FILTER_SIZE][FILTER_SIZE];
	int M = (FILTER_SIZE - 1) / 2;


	//sort columns
	for (int i = 0; i < FILTER_SIZE; i++)
	{
		sort_column(matrix, 0, i);
	}


	//sort rows
	for (int i = 0; i < FILTER_SIZE; i++)
	{
		sort_row(matrix, i, 0);
	}


	//sort diagonals for k=1
	for (int k = 1; k < M + 1; k++)
	{
		for (int s = k*(M + 1); s < k*(M - 1) + FILTER_SIZE; s++)
		{
			sort_diagonals(matrix, k, s, -1);
		}
	}

	//found the median
	return result = matrix[M][M];
}


void sort_column(int mat[FILTER_SIZE][FILTER_SIZE], int row, int col) {
	int min = 256;
	int pos = row;
	int temp;

	for (int i = row; i < FILTER_SIZE; i++)
	{
		if (min > mat[i][col]) {
			pos = i;
			min = mat[i][col];
		}
	}

	temp = mat[row][col];
	mat[row][col] = mat[pos][col];
	mat[pos][col] = temp;

	row++;
	if (row == FILTER_SIZE) return;
	else sort_column(mat, col, row);
}

void sort_row(int mat[FILTER_SIZE][FILTER_SIZE], int row, int col) {
	int min = 256;
	int pos = col;
	int temp;

	for (int i = col; i < FILTER_SIZE; i++)
	{
		if (min > mat[row][i]) {
			pos = i;
			min = mat[row][i];
		}
	}

	temp = mat[row][col];
	mat[row][col] = mat[row][pos];
	mat[row][pos] = temp;

	col++;
	if (col == FILTER_SIZE) return;
	else sort_row(mat, row, col);
}

void sort_diagonals(int mat[FILTER_SIZE][FILTER_SIZE], int k, int s, int step_offset) {
	//line to be sorted: s=k*r+c
	// k=1 s=[3,4,5]  || k=2 s=[6]
	int row, col;
	int startr, startc;
	int max = -1;
	int posc, posr;
	int temp;
	bool done = false;

	row = s / k;
	col = 0;
	if (row > 4) {
		row = 4;
		col = s - row*k;
	}

	row = row - step_offset;
	col = col + step_offset*k;

	if(row <= 0 || col>=4-k) 
		return;

	posr = row;
	posc = col;
	startr = row-1;
	startc = col+k;


	while (row >= 1 && col <= 4 - k)
	{
		col = col + k;
		row--;

		if (max < mat[row][col]) {
			posr = row;
			posc = col;
			max = mat[row][col];
		}


	}

	temp = mat[startr][startc];
	mat[startr][startc] = mat[posr][posc];
	mat[posr][posc] = temp;


	step_offset++;
	sort_diagonals(mat, k, s, step_offset);
}

int border_correction(int imgWidthF, int pos) {

	return pos;
};

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
					ch_result[0] = (short)(*(imgSrcExt + rd_base +  0));
					ch_result[1] = (short)(*(imgSrcExt + rd_base +  1));
					ch_result[2] = (short)(*(imgSrcExt + rd_base +  2));


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