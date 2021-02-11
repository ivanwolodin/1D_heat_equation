#include <iostream>

// #include <unistd.h> // it is working in *nix system for interrupting with sleep(n); where n is a number of seconds

const int  nx = 100; // number of spatial nodes
const int stepTimeNumber = 100000;


// coefficients of the tridiagonal matrix
const double dt = 0.0002 ; // discr. in time
const double dx = 0.1;     // spacial discretixation
const double dx_squared = dx*dx;


/*Constant array (of tridiagonal matrix), 
which is determined from the scratch and won't change
*/
double *mainDiagonal;
double *bellowMainDiagonal;
double *aboveMainDiagonal;


/* the temperature we want to find */
double *T = new double[nx]; 


double *fillInMainDiagonal() {
	/* We'll call it once to fill with values */
	
	double *b = new double[nx];
	for (int i = 0; i < nx; i++) {
		b[i] =  (2*dt/dx_squared + 1);
	}
	
	return b;
}


double *fillInBellowMainDiagonal() {
	/* We'll call it once to fill with values */
	
	double *a = new double[nx];
	a[0] = 0;
	
	for (int i = 1; i < nx; i++) {
		a[i] = -dt/dx_squared;
	}
	
	return a;
}


double *fillInAboveMainDiagonal() {
	/* We'll call it once to fill with values */
	
	double *c = new double[nx];
	for (int i = 0; i < nx-1; i++) {
		c[i] =  - dt/dx_squared;
	}
	
	c[nx-1] = 0;
	return c;
}


double *fillInFreeTerms(double *d) {
	/* Initial distribution */
	
	for (int i = 0; i < nx; i++) {
		d[i] = 0;
	}
	
	d[nx-1] = 1;
	return d;
}


void fillInArrays(){
	/*Fill in all arrays in one function*/
	
	bellowMainDiagonal = fillInBellowMainDiagonal();
	mainDiagonal = fillInMainDiagonal();
	aboveMainDiagonal = fillInAboveMainDiagonal();
	T = fillInFreeTerms(T);
}


double *thomasAlgorithm(double* freeT) {
	/* Since during Thomas alg. solution, we are changing one array, 
	   we need auxilary array to store values
	*/
	double *aboveMain = new double[nx];
	for (int i = 0; i < nx; i++) {
		aboveMain[i] = aboveMainDiagonal[i];
	}
	
	
	// Thomas alg.
    aboveMain[0] = aboveMain[0] / mainDiagonal[0];
    freeT[0] = freeT[0] / mainDiagonal[0];
	
    for (int i = 1; i < nx-1; i++) {
        aboveMain[i] = aboveMain[i] / ( mainDiagonal[i] - bellowMainDiagonal[i]*aboveMain[i-1] );
        freeT[i] = (freeT[i] - bellowMainDiagonal[i]*freeT[i-1]) / (mainDiagonal[i] - bellowMainDiagonal[i]*aboveMain[i-1]);
    }
	
    freeT[nx-1] = (freeT[nx-1] - bellowMainDiagonal[nx-1]*freeT[nx-2]) / (mainDiagonal[nx-1] - bellowMainDiagonal[nx-1]*aboveMain[nx-2]);
	
    for (int i = nx-2; i >= 0; i-- ) {
		freeT[i] -= aboveMain[i]*freeT[i+1];
    }
	
	/*
	Ugly way to debug 
	for (int i = 0; i < nx; i++) {
		std::cout <<freeT[i]  << std::endl;
	}
	sleep(3);
	*/
	
	return freeT;
}


void bc(double* freeT) {
	freeT[0] = 0;
	freeT[nx-1] = 1;	
}


void deallocateArray(double *Arr){
	delete[] Arr; 
}


void deallocateAllArrays(){
	deallocateArray(bellowMainDiagonal);
	deallocateArray(mainDiagonal);
	deallocateArray(aboveMainDiagonal);
	deallocateArray(T);
}


void computeTemperature(){
	for (int stepTime = 0; stepTime < stepTimeNumber; stepTime++) {
		T = thomasAlgorithm(T);
		bc(T);
	}
}


void outputFinalResult(){
	/*Output the final result to console*/
	for (int i = 0; i < nx; i++) {
		std::cout <<T[i]  << std::endl;
	}
}


int main() {

	fillInArrays();
	
	computeTemperature();
	outputFinalResult();
	
	deallocateAllArrays();
	
	return 0;
}
