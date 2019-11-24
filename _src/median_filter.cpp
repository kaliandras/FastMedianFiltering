#include "func.h"
#include "defs.h"
#include <stdio.h>
#include <algorithm>
using namespace std;


int median_filter(int matrix[FILTER_SIZE][FILTER_SIZE])
{
	int result = 0;
	int temp[FILTER_SIZE][FILTER_SIZE];
	int M = (FILTER_SIZE - 1) / 2;

			//printf("original:\n");
			//for (int i = 0; i < 5; i++)
			//{
			//	for (int j = 0; j < 5; j++)
			//	{
			//		printf("%d\t", matrix[i][j]);
			//	}
			//	printf("\n");
			//}
			//printf("\n");

	//sort columns
	sort_column(matrix, 0);
	sort_column(matrix, 1);
	sort_column(matrix, 2);
	sort_column(matrix, 3);
	sort_column(matrix, 4);

	//sort rows
	psort_row(matrix, 0,0);
	psort_row(matrix, 1,0);
	psort_row(matrix, 2,0);
	psort_row(matrix, 3,3);
	psort_row(matrix, 4,2);

	//sort diagonals
	result = get_median(matrix);
	return result;
	
}


void sort_column(int mat[FILTER_SIZE][FILTER_SIZE], int col) {
	int min;
	int pos;
	int temp;

	min = 256;
	for (int i = 0; i < FILTER_SIZE; i++)
	{
		if (min > mat[i][col]) {
			pos = i;
			min = mat[i][col];
		}
	}
	temp = mat[0][col];
	mat[0][col] = mat[pos][col];
	mat[pos][col] = temp;

	min = 256;
	for (int i = 1; i < FILTER_SIZE; i++)
	{
		if (min > mat[i][col]) {
			pos = i;
			min = mat[i][col];
		}
	}
	temp = mat[1][col];
	mat[1][col] = mat[pos][col];
	mat[pos][col] = temp;

	min = 256;
	for (int i = 2; i < FILTER_SIZE; i++)
	{
		if (min > mat[i][col]) {
			pos = i;
			min = mat[i][col];
		}
	}
	temp = mat[2][col];
	mat[2][col] = mat[pos][col];
	mat[pos][col] = temp;

	min = 256;
	for (int i = 3; i < FILTER_SIZE; i++)
	{
		if (min > mat[i][col]) {
			pos = i;
			min = mat[i][col];
		}
	}
	temp = mat[3][col];
	mat[3][col] = mat[pos][col];
	mat[pos][col] = temp;

}

void psort_row(int mat[FILTER_SIZE][FILTER_SIZE], int row, int n) {
	int min;
	int pos;
	int temp;

	min = 256;
	for (int i = 0; i < FILTER_SIZE; i++)
	{
		if (min > mat[row][i]) {
			pos = i;
			min = mat[row][i];
		}
	}
	temp = mat[row][0];
	mat[row][0] = mat[row][pos];
	mat[row][pos] = temp;

	min = 256;
	for (int i = 1; i < FILTER_SIZE; i++)
	{
		if (min > mat[row][i]) {
			pos = i;
			min = mat[row][i];
		}
	}
	temp = mat[row][1];
	mat[row][1] = mat[row][pos];
	mat[row][pos] = temp;

	if (n == 2) return;

	min = 256;
	for (int i = 2; i < FILTER_SIZE; i++)
	{
		if (min > mat[row][i]) {
			pos = i;
			min = mat[row][i];
		}
	}
	temp = mat[row][2];
	mat[row][2] = mat[row][pos];
	mat[row][pos] = temp;

	if (n == 3) return;

	min = 256;
	for (int i = 3; i < FILTER_SIZE; i++)
	{
		if (min > mat[row][i]) {
			pos = i;
			min = mat[row][i];
		}
	}
	temp = mat[row][3];
	mat[row][3] = mat[row][pos];
	mat[row][pos] = temp;
}

int get_median(int mat[FILTER_SIZE][FILTER_SIZE]) {
	int pos;

	int max = -1;
	int mid = -1;
	int min = 256;

	//s=3
	for (int i = 0; i < 4; i++)
	{
		if (max < mat[3 - i][0 + i]) max = mat[3 - i][0 + i];
	}

	//s=4
	int temp[5];
	int mid_max;
	int tp;

		for (int j = 0; j < 5; j++)
		{
			temp[j] = mat[4 - j][0 + j];
		}

		for (int i = 0; i < 3; i++)
		{
			mid_max = -1;
			for (int j = i; j < 5; j++)
			{
				if (mid_max <= temp[j]) {
					mid_max = temp[j];
					pos = j;
				}
			}
			tp = temp[i];
			temp[i] = temp[pos];
			temp[pos] = tp;


			//for (int j = 0; j < 5; j++)
			//{
			//	printf("%d\t",temp[j]);
			//}
			//printf("\n");
		}

		

	mid = temp[2];

	//s=5
	for (int i = 0; i < 4; i++)
	{
		if (min > mat[4 - i][1 + i]) min = mat[4 - i][1 + i];
	}

	//printf("\nmin=%d mid=%d max=%d\n",min,mid,max);

	//s=6
	if (max >= mid && mid >= min) return mid;
	if (max <= mid && mid <= min) return mid;
	
	if (min >= max && max >= mid) return max;
	if (min <= max && max <= mid) return max;

	if (max >= min && min >= mid) return min;
	if (max <= min && min <= mid) return min;


}

//========================================================================================

int median_filter_ref(int matrix[FILTER_SIZE][FILTER_SIZE]) {
	int arr[FILTER_SIZE * FILTER_SIZE];
	int cnt = 0;

	for (int i = 0; i < FILTER_SIZE; i++)
	{
		for (int j = 0; j < FILTER_SIZE; j++)
		{
			arr[cnt] = matrix[i][j];
			cnt++;
		}
	}

	int pos;
	int min = 256;
	int temp;


	for (int i = 0; i < FILTER_SIZE * FILTER_SIZE; i++)
	{
		pos = i;
		min = 256;
		for (int j = i; j < FILTER_SIZE * FILTER_SIZE; j++)
		{
			if (min > arr[j])
			{
				min = arr[j];
				pos = j;
			}

		}
		temp = arr[i];
		arr[i] = arr[pos];
		arr[pos] = temp;
	}

	//for (int i = 0; i < FILTER_SIZE* FILTER_SIZE; i++)
	//{
	//	printf("%d => %d\n",i,arr[i]);
	//}

	return arr[(FILTER_SIZE * FILTER_SIZE - 1) / 2];
}
