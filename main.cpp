# include <iostream>
# include <string>
# include <fstream>

/* It is often used in C++ code. You can just include ALL auxilliary tools by this line, 
but since we need only std output in our code here, we can avoid this massive "dirty" inclusion. 
*/
//using namespace std; 

const int nx = 20; // discretization number
const int timeStepsNumbers = 10000; // number of time steps

/*In numerical methods it is crucially important to follow for the solution consistency and 
for stabillity of your code. In diffusion equation which we are solving here stabilityCondition constant 
is the representation Courant number. It is responsible for the stabillity. 
If we change it to 1.0 then we won't get a consistent result, our code will converge, 
so we need to pay attention to this 
*/
const float stabilityCondition = 0.1;

/*we will output the result once in 100 steps*/
const int periodOfOutput = 100;


void boundaryConditions(float *T){ // asterisk means that the value is passing to the function by ...
	/* Since the stub is cooled from the left side T[0] = 0 
	and is heated from the right side T[nx] = 1 
	*/
	
	T[0] = 0;
	T[nx] = 1;
}


void outputToFile(float *T, int step){
	/* we need to save inbetween results. 
	It is common practice to save it to the file named by step number
	*/
	
	std::string filename = std::to_string(step);
	/*It is better to save the results to a specific folder result. 
	You can create that folder and uncomment below line and comment the line in commented scope
	//std::ofstream outfile ("result/" + filename + ".dat");
	and comment the next line
	*/
	std::ofstream outfile (filename + ".dat");
	
	for (int i=0; i <= nx; i++){
		outfile <<i<< "  "<< T[i]<< std::endl;
	}	
}


void solveOneDimHeatEquation(float *T, float *previousT){
	/* The core function, which is responsible for the solution finding */
	
	/* main time loop */
	for (int t=0; t <= timeStepsNumbers; t++){
			
			/* First we need an array to save the previous results */
			for (int i=0; i <= nx; i++){
				previousT[i] = T[i] ;
			}		
			
			/* We are iterating over the whole spacial steps */
			for (int i=1; i < nx; i++){
				
				/*Explicit scheme: 
					      T(X,T+dt) - T(X,T)                  ( T(X-dx,T) - 2 T(X,T) + T(X+dx,T) )
					      ------------------  = T(X,T) + k *  ------------------------------------
					               dt                                   dx * dx					
								   
				or after some trivial calculation: 
						T(X,T+dt) = T(X,T) + stabilityCondition * ( T(X-dx,T) - 2 T(X,T) + T(X+dx,T) ) 
				*/
				
				T[i] = previousT[i] + stabilityCondition * (previousT[i + 1] - 2 * previousT[i] + previousT[i - 1]) ;
				
			}
			
			/* we need our bc to affect out solution. 
			   Bc are in our case is the represention of physical statement of our problem  
			
			*/
			boundaryConditions(T);
			
			/* And we need the output to see the evolution in time. 
				How the stub is heating. We are following the heating diffusion here
			*/
			if (t % periodOfOutput == 0) {
				outputToFile(T, t);
			}
		}
}


float *allocateArray(){
	/*we need to allocate an array to use this memory as a storage for our solution*/
	
	float* Arr = new float[nx];
	for (int i=0; i <= nx; i++){
			Arr[i] = 0;
		}
	return Arr;
}


void outputFinalResult(float *T){
	std::cout << "Solution of heat equation by explicit scheme:";
	for (int i=0; i <= nx; i++){
	  std::cout <<T[i];
	  std::cout <<std::endl;
  }
}


void deallocateArray(float *Arr){
	delete[] Arr; 
}


int main ( )
{	
	/*In IT it is common practice to build your code from different "blocks" and then construct from them 
	a working instance. That is way if you think that some piece of your code can find its implementation in some 
	"standalone" function, probably it is a good way to put that functionality in that methoid. It makes your code clean :)
	*/
	
	float* T = allocateArray();
    float* previousT = allocateArray(); 
 
	solveOneDimHeatEquation(T, previousT);
	outputFinalResult(T);
	
	deallocateArray(T);
	deallocateArray(previousT);
  
	return 0;
}

