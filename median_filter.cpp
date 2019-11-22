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


	//sort diagonals
	//for (int k = 1; k < M + 1; k++)
	//{
	//	for (int s = k*(M + 1); s < k*(M - 1) + FILTER_SIZE; s++)
	//	{
	//		sort_diagonals(matrix, k, s, -1);
	//	}
	//}
	result = sort_diagonals_shortcut(matrix);
	return result;

	//found the median
	//return result = matrix[M][M];
	
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

	if (row <= 0 || col >= 4 - k)
		return;

	posr = row;
	posc = col;
	startr = row - 1;
	startc = col + k;


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

using namespace std;
int median_filter_ref(int matrix[FILTER_SIZE][FILTER_SIZE]) {
	int arr[FILTER_SIZE*FILTER_SIZE];
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


	for (int i = 0; i < FILTER_SIZE*FILTER_SIZE; i++)
	{
		pos = i;
		min = 256;
		for (int j = i; j < FILTER_SIZE*FILTER_SIZE; j++)
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


	return arr[(FILTER_SIZE*FILTER_SIZE - 1) / 2];
}

int sort_diagonals_shortcut(int mat[FILTER_SIZE][FILTER_SIZE]) {
	//line to be sorted: s=k*r+c
	// k=1 s=[3,4,5]  || k=2 s=[6]

	int mid_max = -1;
	int temp;
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
	for (int i = 0; i < 3; i++)
	{
		int mid_max = -1;
		for (int j = i; j < 5; j++)
		{
			if (mid_max < mat[4 - j][0 + j]) {
				mid_max = mat[4 - j][0 + j]; 
				pos = j;
			}
		}
		temp = mat[4 - i][0 + i];
		mat[4 - i][0 + i] = mat[4 - pos][0 + pos];
		mat[4 - pos][0 + pos]= mat[4 - i][0 + i];
	}
	mid = mat[2][2];

	//s=5
	for (int i = 0; i < 4; i++)
	{
		if (min > mat[4 - i][1 + i]) min = mat[4 - i][1 + i];
	}

	//s=6
	if (max >= mid && mid >= min) return mid;
	if (max <= mid && mid <= min) return mid;
	
	if (min >= max && max >= mid) return max;
	if (min <= max && max <= mid) return max;

	if (max >= min && min >= mid) return min;
	if (max <= min && min <= mid) return min;


}
