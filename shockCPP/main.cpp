/*
    Problem: CFD solver for the unsteady Couette flow
    
    Unsteady state solver, converges at a residual rate of 0.01. Gauss-sidel linear
    solver was implemented, as well as residual convergence
   
    compile: g++ *.cpp  -o Couette.run
*/

#include <iostream>
//#include "mesh.h"
#include "solver.h"

int main()
{
  
    Mesh mesh(-7.0,7.0,141); //141
    
    mesh.setField("velocity"   ,-7 , 7,     0);
    mesh.setField("pressure"   ,-7 , 0,988000);
    mesh.setField("pressure"   , 0 , 7, 99300);
    mesh.setField("temperature",-7 , 0,  2438);
    mesh.setField("temperature", 0 , 7,  2452);

    mesh.initiateThermoPhysicalProperties(1005,718);

    if( mesh.checkFields() == -1){ cout << "\nProgram Terminated! \n"; return 0; }

    Solver EQNmass(     mesh, &Mesh::getRho,  &Mesh::getRhoFlux  );
    Solver EQNmomentum( mesh, &Mesh::getRhoU, &Mesh::getRhoUFlux );
    Solver EQNenergy(   mesh, &Mesh::getRhoE, &Mesh::getRhoEFlux );

    double time = 0;
    double timestep = 0.001;

    while(time < 0.3) // main time loop;
    {
        EQNmass.advanceTime(timestep);
        EQNmomentum.advanceTime(timestep);
        EQNenergy.advanceTime(timestep);

        mesh.printVTK(time);

        time += timestep; 
    }
    
    cout << "\nProgram Terminated! \n"; return 0;
    return 0;
}


