#ifndef FUNC_H
#define FUNC_H

#include "defs.h"

//traverses trough the image, creates the pixel matrices for the filtering
void img_filter(int imgHeight, int imgWidth, int imgWidthF, unsigned char *imgSrcExt, unsigned char *imgDst);

//traverses the images, tests if reading then writing pixels works properly (and if the positioning is good)
void img_read_write_test(int imgHeight, int imgWidth, int imgWidthF, unsigned char *imgSrcExt, unsigned char *imgDst);

//checks for filtering errors
void img_filter_test(int imgHeight, int imgWidth, int imgWidthF, unsigned char *imgSrcExt, unsigned char *imgDst);

//============================================================================================================
//============================================================================================================

//finds a given matrix's median
int median_filter(int matrix[FILTER_SIZE][FILTER_SIZE]);

//median filter with a foolproof but expensive algirithm for reference
int median_filter_ref(int matrix[FILTER_SIZE][FILTER_SIZE]);

//============================================================================================================
//============================================================================================================

//sorts the columns of a matrix in an ascending order
void sort_column(int mat[FILTER_SIZE][FILTER_SIZE], int col);

//partially sorts 'n' components the rows of a matrix in an ascending order to the front or back 
void psort_row(int mat[FILTER_SIZE][FILTER_SIZE], int row,int n);

//gets the median value: partially sorts s=3,4,5 diagonals and returns with the median
int get_median(int mat[FILTER_SIZE][FILTER_SIZE]);
#endif
