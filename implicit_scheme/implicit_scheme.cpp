#include <iostream>

#include <unistd.h>

const int  n = 30;
const int stepTimeNumber = 100000;

const double dt = 0.1;
const double dx = 0.05;
const double dx_squared = dx*dx;

double *a = new double[n];
double *b = new double[n];
double *c = new double[n];
	
	
double *fillInMainDiagonal(double *b) {
	for (int i = 0; i < n; i++) {
		b[i] =  (2*dt/dx_squared - 1);
	}
	
	return b;
}


double *fillInBellowMainDiagonal(double *a) {
	for (int i = 0; i < n; i++) {
		a[i] = dt/dx_squared;
	}
	
	a[0] = 0;
	return a;
}


double *fillInAboveMainDiagonal(double *c) {
	for (int i = 0; i < n; i++) {
		c[i] =  - dt/dx_squared;
	}
	
	c[n-1] = 0;
	return c;
}


double *thomasAlgorithm(double* d) {

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
	
	c = fillInAboveMainDiagonal(c);
	
	return d;
}


double bc(double* d) {
	d[0] = 0;
	d[n-1] = 1;	
}


double *fillInFreeTerms(double *d) {
	for (int i = 0; i < n; i++) {
		d[i] = 0;
	}
	
	d[n-1] = 1;
	return d;
}


void deallocateArray(double *Arr){
	delete[] Arr; 
}


int main() {

	a = fillInBellowMainDiagonal(a);
	b = fillInMainDiagonal(b);
	c = fillInAboveMainDiagonal(c);
	
	double *d = new double[n];
	d = fillInFreeTerms(d);

	
	for (int stepTime = 0; stepTime < stepTimeNumber; stepTime++) {
		d = thomasAlgorithm(d);
		bc(d);
	}
	
	for (int i = 0; i < n; i++) {
		std::cout <<d[i]  << std::endl;
	}
	
	deallocateArray(a);
	deallocateArray(b);
	deallocateArray(c);
	deallocateArray(d);
	
	return 0;
}
