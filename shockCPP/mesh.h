#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class Mesh {

    // Properties of the mesh
    double totalsize;
    double firstcoordinate;
    double delta;
    int    numberofpoints;

    double *points;   

    // System variables
    double *U;        // Velocity
    double *E;        // Energy    
    double *rho;      // Density

    // System explicitely calculated variables
    double *rhoU;     // Momentum
    double *rhoE;     // Energy momentum
    double *rhoFlux;  // Flux for density equation
    double *rhoUFlux; // Flux for momentum equation  
    double *rhoEFlux; // Flux for energy equation
    double *p;        // Pressure
    double *T;        // Temperature    
    double *macno;    // Mac number

    // Static global properties of the fluid
    double k;         // c_p /c_v = const
    double cv;        // C_v  [J/kg.K]
    double cp;        // C_p  [J/kg.K]
    double R;         // R_specific [J Kg^-1 K^-1]

public:

    Mesh(double meshbegin, double meshend, int numberofmeshpoints);

    int    checkFields();

    void   setField(string field, double begincoord, double endcoord, double value);   
    void   initiateVariables(double cpinput, double cvinput);    
    void   updateVariables();
    void   updateFluxes();
    void   updateBoundaryConditions();
    
    // Access to variables
    double*  getRho();
    double*  getRhoU(); 
    double*  getRhoE();

    double*  getRhoFlux();
    double*  getRhoUFlux(); 
    double*  getRhoEFlux();

    // Access to constants
    double getk();      
    double getcv();     
    double getcp();    

    int    getNumberofPoints();
    double getDelta();

    void   printVTK(double timestep);

};