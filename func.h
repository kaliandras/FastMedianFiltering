#ifndef FUNC_H
#define FUNC_H

#include "defs.h"

//traverses trough the image, creates the pixel matrices for the filtering
void extract_data(int imgHeight, int imgWidth, int imgWidthF, unsigned char *imgSrcExt, unsigned char *imgDst);

//traverses the images, tests if reading then writing pixels works properly (and if the positioning is good)
void img_read_write_test(int imgHeight, int imgWidth, int imgWidthF, unsigned char *imgSrcExt, unsigned char *imgDst);

//checks if the a pixel we center a filtering windows around is too near to the border of the image
//int border_correction(int imgWidthF, int imgHeight, int pos, int window_offset);

//finds a given matrix's median
int medianFilter(int matrix[FILTER_SIZE][FILTER_SIZE]);

//median filter with a foolproof but expensive algirithm for reference
int median_filter_ref(int matrix[FILTER_SIZE][FILTER_SIZE]);

//sorts the columns of a matrix in an ascending order
void sort_column(int mat[FILTER_SIZE][FILTER_SIZE], int row, int col);

//sorts the rows of a matrix in an ascending order
void sort_row(int mat[FILTER_SIZE][FILTER_SIZE], int row, int col);

//sorts a diagonal s=k*r+c of the matrix, where s selects the diagonal and k indicates the slope
void sort_diagonals(int mat[FILTER_SIZE][FILTER_SIZE], int k, int s, int step_offset);

#endif
