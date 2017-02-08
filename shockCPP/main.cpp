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
  
    Mesh mesh(-7.0,7.0,141); //141

    mesh.setField("velocity"   ,-7 , 7,     0);
    mesh.setField("pressure"   ,-7 , 0,988000);
    mesh.setField("pressure"   , 0 , 7, 99300);
    mesh.setField("temperature",-7 , 0,  2438);
    mesh.setField("temperature", 0 , 7,  2452);

    mesh.initiateThermoPhysicalProperties(1.005,0.718);

    if( mesh.checkFields() == -1){ cout << "\nProgram Terminated! \n"; return 0; }

    

    mesh.printVTK(0);

    return 0;
}


