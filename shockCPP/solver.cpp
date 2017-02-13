#include "solver.h"

Solver::Solver(double* vectorU, double* vectorUflux, int numberofpoints){

    U     = vectorU;       
    Uflux = vectorUflux;    

    n = numberofpoints;
};

void Solver::advanceTime(double deltaTinput){
	
	deltaT = deltaTinput;

    for(int i=1; i<n-1; i++)
    {
        U[i] = U[i] - deltaT * Uflux[i];
    }

}