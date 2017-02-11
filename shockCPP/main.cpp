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
  
    Mesh mesh(-7.0,7.0,5); //141
    
    mesh.setField("velocity"   ,-7 , 7,     0);
    mesh.setField("pressure"   ,-7 , 0,988000);
    mesh.setField("pressure"   , 0 , 7, 99300);
    mesh.setField("temperature",-7 , 0,  2438);
    mesh.setField("temperature", 0 , 7,  2452);

    mesh.initiateThermoPhysicalProperties(1005,718);

    if( mesh.checkFields() == -1){ cout << "\nProgram Terminated! \n"; return 0; }

    Solver EQN_r(     mesh, &Mesh::getRho,  &Mesh::getRhoFlux  );
    Solver EQN_U( mesh, &Mesh::getRhoU, &Mesh::getRhoUFlux );
    Solver EQN_E(   mesh, &Mesh::getRhoE, &Mesh::getRhoEFlux );

    double starttime = 0;
    double timestep  = 0.00001;
    double endtime   = 0.00004;
    int    nprints;
    int    maxprints = 10;

    mesh.printVTK(0);

    for (double time = starttime+timestep; time <= endtime; time +=timestep ) // main time loop;
    {
        cout << "current time: " << time <<"\n";

        EQN_r.advanceTime(timestep);
        EQN_U.advanceTime(timestep);
        EQN_E.advanceTime(timestep);

        mesh.updateRho(EQN_r.updatedField());
        mesh.updateU(  EQN_U.updatedField());
        mesh.updateE(  EQN_E.updatedField());

        mesh.updateBoundaryConditions();
        mesh.updateThermoPhysicalProperties();

        mesh.printVTK(time);   
    }
    

    cout << "\nProgram Terminated! \n"; return 0;
    return 0;
}


