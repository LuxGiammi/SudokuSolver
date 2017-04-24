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
			return true;
	}
	return false;
}

bool checkColumn(uchar sudoku[][SUDOKU_SIZE], size_t c, uchar num) {
	for (size_t i = 0; i < SUDOKU_SIZE; i++)
	{
		if (sudoku[i][c] == num)
			return true;
	}
	return false;
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
				return true;
			}
		}
	}

	return false;
}

void sudokuSolver(uchar sudoku[][SUDOKU_SIZE], size_t r, size_t c, bool foundSolution) {
	//Read the matrix by rows: if I have r >= SUDOKU_SIZE, I increment the column and reset the row number
	if (r >= SUDOKU_SIZE) {
		r = 0;
		c++;
	}

	//If the c >= SUDOKU_SIZE, I've solved the sudoku
	if (c >= SUDOKU_SIZE)
	{
		foundSolution = true;
	}

	//I'm considering row = r, and column = c:
	//Try to put here a number

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

}