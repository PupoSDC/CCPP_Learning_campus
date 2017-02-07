/*
    Problem: CFD solver for the unsteady Couette flow
    
    Unsteady state solver, converges at a residual rate of 0.01. Gauss-sidel linear
    solver was implemented, as well as residual convergence
   
    compile: g++ *.cpp  -o Couette.run
*/

#include <iostream>
#include "mesh.h"


int main()
{
  
    Mesh mesh(1,11);
   
    mesh.setBoundaries(0.0,10);
    mesh.setPhisicalProperties(1);
    mesh.setTimeProperties(1,1);


    mesh.printMeshValues();

    while( mesh.getResidual() > 0.01 )
    {
        mesh.advanceTime();
        mesh.printMeshValues();
    }
    
    printf("Convergence to steady state occured at t = %3.2f",mesh.getTime());
    return 0;
}

