#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
//gcc program.c -lgsl -lgslcblas -lm -o program

void saveTime(FILE *fp, char *type, int vSize, clock_t start, clock_t end) {
	//save time and size to file
	fprintf(fp, "%s, %d, %f\n", type, vSize, ((double) (end - start)) / CLOCKS_PER_SEC); 
}

void ddot(FILE *fp, int vSize, gsl_vector *A, gsl_vector *B) {
	clock_t start, end;
	double result = 0;

	start = clock();
	gsl_blas_ddot(A, B, &result);
	end = clock();

	//save time and size to file
	saveTime(fp, "ddot", vSize, start, end);
}

void dgemv(FILE *fp, int vSize, gsl_vector *A) {
	clock_t start, end;
	gsl_matrix *M = gsl_matrix_alloc(vSize, vSize);
	gsl_vector *B = gsl_vector_alloc(vSize);

	for(int i = 0; i < vSize; i++) {
		for(int j = 0; j < vSize; j++) {
			gsl_matrix_set(M, i, j, (double) rand() * i / (double) (rand() + 1));
		}
		gsl_vector_set(B, i, rand() * i / (rand() + 1));
	}
	
	start = clock();
	gsl_blas_dgemv(CblasNoTrans, 1.0, M, A, 0.0, B);
	end = clock();
	saveTime(fp, "dgemv", vSize, start, end);
	
	gsl_matrix_free(M);
	gsl_vector_free(B);
	
}

void measure(FILE *fp, int size) {	
	gsl_vector *x = gsl_vector_alloc(size);
	gsl_vector *y = gsl_vector_alloc(size);
	for(int t = 0; t < 10; t++) {
		for(int i = 0; i < size; i++) {
			gsl_vector_set(x, i, rand() * i / (rand() + 1));
			gsl_vector_set(y, i, rand() * i / (rand() + 1));
		}
		ddot(fp, size, x, y);
		dgemv(fp, size, x);
	}

	gsl_vector_free(x);
	gsl_vector_free(y);
}																																																																																																																																																							

int main (void) {
	//uruchomić i zmierzyć czasy działania obydwu funkcji dla różnych rozmiarów wektorów -> 10 pomiarów dla każdego rozmiaru wektora
	FILE *fp;
	srand(time(NULL));
	fp = fopen("wyniki.csv", "w+");
	fprintf(fp, "typ, rozmiar, czas\n"); //make headline
	
	for(int i = 100; i < 1000; i += 100) {
		int n = i;
			measure(fp, n);
			n += i;
	}
	
	fclose(fp);
	return 0;
}
