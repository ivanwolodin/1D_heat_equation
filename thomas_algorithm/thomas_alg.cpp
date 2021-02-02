#include <iostream>
const int  n = 3;

double *thomasAlgorithm(double* a, double* b, double* c, double* d) {

    c[0] = c[0] / b[0];
    d[0] = d[0] / b[0];
	
    for (int i = 1; i < n-1; i++) {
        c[i] = c[i] / ( b[i] - a[i]*c[i-1] );
        d[i] = (d[i] - a[i]*d[i-1]) / (b[i] - a[i]*c[i-1]);
    }
	
    d[n-1] = (d[n-1] - a[n-1]*d[n-2]) / (b[n-1] - a[n-1]*c[n-2]);
	
    for (int i = n-2; i >= 0; i-- ) {
		d[i] -= c[i]*d[i+1];
    }
	
	return d;
}

int main() {
		
	/*
	// FIRST EXAMPLE const int  n = 5;
	
	double a[n] = { 0, -3, -5, -6, -5 };
	double b[n] = { 2,  8,  12,  18, 10 };
	double c[n] = {-1, -1, 2,  -4, 0 };
	double d[n] = { -25,  72, -69, -156, 20 };
	
	double *result = thomasAlgorithm(a,b,c,d);
	// results    {-10,  5,  -2, -10, -3  }
	*/
	
	// SECOND EXAMPLE const int  n = 3;
	double a[n] = { 0, 5, 1 };
	double b[n] = { 2,  4,  -3 };
	double c[n] = {-1, 2, 0};
	double d[n] = { 3, 6, 2};
	
	double *result = thomasAlgorithm(a,b,c,d);
	// results    {1.4 , -0.02, -0.67  }
	for (int i = 0; i < n; i++) {
		std::cout << result[i] << std::endl;
	}

	return 0;
}
