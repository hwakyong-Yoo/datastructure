#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int x, y, z = 0;

double*** mem_alloc_3D_double() {
	double*** m3 = (double***)malloc(sizeof(double**) * x); 
	for (int i = 0; i < x; i++) {
		m3[i] = (double**)malloc(sizeof(double*) * y);
		for (int j = 0; j < y; j++) {
			m3[i][j] = (double*)malloc(sizeof(double) * z);
		}
	}
	return m3;
}


void addition_3D(double*** input1, double*** input2, double*** output) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int q = 0; q < z; q++) {
				output[i][j][q] = input1[i][j][q] + input2[i][j][q];
				printf("matrix[%d][%d][%d] \= %f\n", i, j, q, output[i][j][q]);
			}
		}
	}
	printf("\n");
}

void deallocate_3D_double(double*** m) {
	if (m != NULL) {
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				free(m[i][j]);
			}
			free(m[i]);
		}
		free(m);
		m = NULL;
	}
}

void assignMatrix(double*** m) {
	int count = 0;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int q = 0; q < z; q++) {
				printf("matrix[%d][%d][%d] \= ", i, j, q);
				scanf_s("%lf", &m[i][j][q]);
			}
		}
	}
}

int main() {
	//Define two matrices A and B using 'mem_alloc_3D_double'
	printf("input x, y, z : ");
	scanf_s("%d %d %d", &x, &y, &z);

	double*** A = mem_alloc_3D_double();
	double*** B = mem_alloc_3D_double();
	double*** C = mem_alloc_3D_double();

	//assign
	printf("Matrix A\n");
	assignMatrix(A);
	printf("Matrix B\n");
	assignMatrix(B);

	printf("\n");
	//Perform addtion of two matrices using 'addition_3D()'
	addition_3D(A, B, C);

	//Deallocate A and B
	deallocate_3D_double(A);
	deallocate_3D_double(B);
	return 0;
}