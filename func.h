#ifndef FUNC_H
#define FUNC_H

#include "defs.h"

//traverses trough the image, creates the pixel matrices for the filtering
void extract_data(int imgHeight, int imgWidth, int imgWidthF,
	 unsigned char *imgSrcExt, unsigned char *imgDst);

void img_read_write_test(int imgHeight, int imgWidth, int imgWidthF, unsigned char *imgSrcExt, unsigned char *imgDst);

//finds a given matrix's median
int medianFilter(int matrix[FILTER_SIZE][FILTER_SIZE]);

//sorts the columns of a matrix in an ascending order
void sort_column(int mat[FILTER_SIZE][FILTER_SIZE], int row, int col);

//sorts the rows of a matrix in an ascending order
void sort_row(int mat[FILTER_SIZE][FILTER_SIZE], int row, int col);

//sorts a diagonal s=k*r+c of the matrix, where s selects the diagonal and k indicates the slope
void sort_diagonals(int mat[FILTER_SIZE][FILTER_SIZE], int k, int s, int step_offset);




#endif
