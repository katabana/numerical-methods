#include <stdio.h>
#include <math.h>
double e = 2.71828182846;

void f(int n) {
	double y = 1 - pow(e, -1);
	for(double i = 1.0; i < n; i++) {
		y = 1 - i * y;
	}
	printf("	I: %f\n", y);
}

void g(int n) {
	double N = 100.0;
	double y = 0;
	for(double i = N; i >= n; i--) {
		y = 1 / i * (1 - y);
		
	}
	printf("	II: %f\n", y);
}

int main(){
	printf("n = 10\n");
	f(10);
	g(10);
	printf("n = 11\n");
	f(11);
	g(11);
	printf("n = 16\n");
	f(16);
	g(16);
	printf("n = 30\n");
	f(30);
	g(30);

	return 0;
}
