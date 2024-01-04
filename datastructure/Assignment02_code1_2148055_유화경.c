#include <stdio.h>
#define ROWS 3
#define COLS 3
#define MAX_TERMS 10

typedef struct {
	int row;
	int col;
	int value;
} element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
} SparseMatrix;

SparseMatrix transSparseMatrix(SparseMatrix matrix) {
	SparseMatrix transMat = { 0 };

	int currentTerm = 0;
	for (int col = 0; col < matrix.cols; col++) {
		for (int i = 0; i < matrix.terms; i++) {
			if (matrix.data[i].col == col) {
				transMat.data[currentTerm].row = matrix.data[i].col;
				transMat.data[currentTerm].col = matrix.data[i].row;
				transMat.data[currentTerm].value = matrix.data[i].value;
				currentTerm++;
			}
		}
	}
	transMat.terms = currentTerm;
	return transMat;
}



void printMat(SparseMatrix m) {
	int array[ROWS][COLS] = { 0 };
	int term = m.terms;

	for (int i = 0; i < m.terms; i++) {
		array[m.data[i].row][m.data[i].col] = m.data[i].value;
	}
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
}

int main() {
	SparseMatrix B = {
		{{0, 1, 1}, {1, 2, 2}, {2, 0, 3}},
		ROWS, 
		COLS, 
		3
	};

	SparseMatrix Bt = transSparseMatrix(B);

	printMat(B);
	printf("\n");
	printMat(Bt);

	return 0;
}
