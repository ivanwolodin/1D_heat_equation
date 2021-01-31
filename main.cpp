# include <iostream>

//using namespace std; 

const int nx = 20;
const int stepsNumbers = 1000;

const float stabillityParameter = 0.1;


void boundaryConditions(float *T){
	T[0] = 0;
	T[nx] = 1;
}


void solveOneDimHeatEquation(float *T, float *previousT){
	for (int t=0; t<=stepsNumbers; t++){
	  
			for (int i=0; i<=nx; i++){
				previousT[i] = T[i] ;
			}		
	  
			for (int i=1; i<nx; i++){
				T[i] = previousT[i] + stabillityParameter *(previousT[i + 1] - 2 * previousT[i] + previousT[i - 1]) ;
			}
			boundaryConditions(T);
		}
}


float *allocateArray(){
	float* Arr = new float[nx];
	for (int i=0; i<=nx; i++){
			Arr[i] = 0;
		}
	return Arr;
}


void outputResult(float *T){
	for (int i=0; i<=nx; i++){
	  std::cout <<T[i];
	  std::cout <<std::endl;
  }
}


int main ( )
{
	float* T = allocateArray();
    float* previousT = allocateArray(); 
 
	solveOneDimHeatEquation(T, previousT);
	outputResult(T);
  
	return 0;
}

