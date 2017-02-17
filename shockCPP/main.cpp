/*
    Problem: CFD solver for the unsteady Couette flow
    
    Unsteady state solver, converges at a residual rate of 0.01. Gauss-sidel linear
    solver was implemented, as well as residual convergence
   
    compile:  g++ *.cpp -std=c++11 -o shock.run
*/

#include <iostream>
#include "mesh.h"
#include "solver.h"
    
int main()
{
  
    Mesh mesh(-0.5,0.5,1001); //141
    
    mesh.setField("velocity"   ,-0.5, 0.5,     0);
    mesh.setField("temperature",-0.5, 0.5,   303);
    mesh.setField("pressure"   ,-0.5, 0.0,500000);
    mesh.setField("pressure"   , 0.0, 0.5, 20000);

    //Mesh mesh(-7.0,7.0,1001); //141

    //mesh.setField("velocity"   ,-7 , 7,     0);
    //mesh.setField("pressure"   ,-7 , 0,988000);
    //mesh.setField("pressure"   , 0 , 7, 99300);
    //mesh.setField("temperature",-7 , 0,  2438);
    //mesh.setField("temperature", 0 , 7,  2452);


    mesh.initiateVariables(1005,718);

    if( mesh.checkFields() == -1){ cout << "\nProgram Terminated! \n"; return 0; }

    Solver EQN_r( mesh.getRho(),  mesh.getRhoFlux(),  mesh.getNumberofPoints() );
    Solver EQN_U( mesh.getRhoU(), mesh.getRhoUFlux(), mesh.getNumberofPoints() );
    Solver EQN_E( mesh.getRhoE(), mesh.getRhoEFlux(), mesh.getNumberofPoints() );

    double starttime = 0;
    double timestep  = 0.000001;
    double printstep = 0.00010;
    double endtime   = 0.00400;

    mesh.printVTK(0);

    // main time loop;
    for (double time = starttime + timestep, printtime = starttime + printstep; time <= endtime; time +=timestep ) 
    {
        cout << "current time: " << time <<"\n";
        
        EQN_r.advanceTime(timestep); 
        EQN_U.advanceTime(timestep); 
        EQN_E.advanceTime(timestep); 

        mesh.updateVariables();

        if( time >= printtime )
        {
           mesh.printVTK(time); 
           printtime += printstep;
        }
        
    }
    
    cout << "\nProgram Terminated! \n"; return 0;
    return 0;
}


