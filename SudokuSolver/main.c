#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ELEMENTARY_MATRIX_SIZE 3
#define SUDOKU_SIZE ELEMENTARY_MATRIX_SIZE * ELEMENTARY_MATRIX_SIZE

typedef unsigned char uchar;

bool checkRow(uchar sudoku[][SUDOKU_SIZE], size_t r, uchar num) {
	for (size_t i = 0; i < SUDOKU_SIZE; i++)
	{
		if (sudoku[r][i] == num)
			return false;
	}
	return true;
}

bool checkColumn(uchar sudoku[][SUDOKU_SIZE], size_t c, uchar num) {
	for (size_t i = 0; i < SUDOKU_SIZE; i++)
	{
		if (sudoku[i][c] == num)
			return false;
	}
	return true;
}

bool checkSubmatrix(uchar sudoku[][SUDOKU_SIZE], size_t r, size_t c, uchar num) {
	//Getting submatrix:
	size_t sr = r / (ELEMENTARY_MATRIX_SIZE), sc = c / (ELEMENTARY_MATRIX_SIZE);

	for (size_t isc = 0; isc < ELEMENTARY_MATRIX_SIZE; isc++)
	{
		for (size_t isr = 0; isr < ELEMENTARY_MATRIX_SIZE; isr++)
		{
			//Getting cell in sudoku matrix: [sr * 3][sc*3] is the top-left cell of the submatrix.
			if (sudoku[sr * 3 + isr][sc * 3 + isc] == num) {
				return false;
			}
		}
	}

	return true;
}

void sudokuSolver(uchar sudoku[][SUDOKU_SIZE], size_t r, size_t c, bool foundSolution) {
	//Read the matrix by rows: if I have r >= SUDOKU_SIZE, I increment the column and reset the row number
	if (c >= SUDOKU_SIZE) {
		c = 0;
		r++;
	}

	//If the c >= SUDOKU_SIZE, I've solved the sudoku
	if (r >= SUDOKU_SIZE)
	{
		foundSolution = true;
	}

	//I'm considering row = r, and column = c:
	//Try to put here a number
	if (sudoku[r][c] == 0) {
		for (uchar i = 1; i <= 9; i++)
		{
			if (checkRow(sudoku, r, i) && checkColumn(sudoku, c, i) && checkSubmatrix(sudoku, r, c, i)) {
				//i can go in [r][c]
				sudoku[r][c] = i;
				//Recursive call for sudoku
				sudokuSolver(sudoku, r, c+1, foundSolution);
				if (foundSolution)
					return;			//No need to continue: return.
			}
		}
		return;
	}
	else {
		sudokuSolver(sudoku, r, c+1, foundSolution);
	}
}

void LoadSudokuFromFile(char *filename, uchar sudoku[][SUDOKU_SIZE]) {
	FILE *f = fopen(filename, "rt");
	for (size_t r = 0; r < SUDOKU_SIZE; r++)
	{
		for (size_t c = 0; c < SUDOKU_SIZE; c++)
		{
			int n;
			fscanf(f, "%d ", &n);
			sudoku[r][c] = (uchar)n;
		}
	}
	fclose(f);
}

void PrintSudokuToFile(char *filename, uchar sudoku[][SUDOKU_SIZE]) {
	FILE *f = fopen(filename, "wt");
	for (size_t r = 0; r < SUDOKU_SIZE; r++)
	{
		for (size_t c = 0; c < SUDOKU_SIZE; c++)
		{
			fprintf(f, "%d ", sudoku[r][c]);
		}
		fputc('\n', f);
	}
	fclose(f);
}

int main() {
	/*
	RULES:
	9x9 matrix divided into 9 3x3 submatricies starting from the top-left corner.
	|=====*=====*=====|=====*=====*=====|=====*=====*=====|
	|     *     *     |     *     *     |     *     *     |
	|-----*-----*-----|-----*-----*-----|-----*-----*-----|
	|     *     *     |     *     *     |     *     *     |
	|-----*-----*-----|-----*-----*-----|-----*-----*-----|
	|     *     *     |     *     *     |     *     *     |
	|=====*=====*=====|=====*=====*=====|=====*=====*=====|
	|     *     *     |     *     *     |     *     *     |
	|-----*-----*-----|-----*-----*-----|-----*-----*-----|
	|     *     *     |     *     *     |     *     *     |
	|-----*-----*-----|-----*-----*-----|-----*-----*-----|
	|     *     *     |     *     *     |     *     *     |
	|=====*=====*=====|=====*=====*=====|=====*=====*=====|
	|     *     *     |     *     *     |     *     *     |
	|-----*-----*-----|-----*-----*-----|-----*-----*-----|
	|     *     *     |     *     *     |     *     *     |
	|-----*-----*-----|-----*-----*-----|-----*-----*-----|
	|     *     *     |     *     *     |     *     *     |
	|=====*=====*=====|=====*=====*=====|=====*=====*=====|

	Those cells are filled with numbers by following these rules:
		1. Each row contains all numbers from 1 to 9 exactly once.
		2. Each column contains all numbers from 1 to 9 exactly once.
		3. Each submatrix contains all numbers from 1 to 9 exactly once.

	Some hints are given at start (some cells are already filled).
	The problem is: fill the remaining cells following the rules given before.
	*/

	uchar sudoku[SUDOKU_SIZE][SUDOKU_SIZE];

	//Fill sudoku in any way.

	LoadSudokuFromFile("example.sudoku", sudoku);

	//Call sudoku:
	sudokuSolver(sudoku, 0, 0, false);

	//Print solution to a file:
	PrintSudokuToFile("solution.sudoku", sudoku);

	return 0;
}