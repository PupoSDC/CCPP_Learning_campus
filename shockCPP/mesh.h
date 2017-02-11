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
    double *p;        // Pressure
    double *T;        // Temperature    
    double *macno;    // Mac number

    // Static global properties of the fluid
    double k;         // c_p /c_v = const
    double cv;        // C_v  [J/kg.K]
    double cp;        // C_p [J/kg.K]

public:

    Mesh(double meshbegin, double meshend, int numberofmeshpoints);

    void   setField(string field, double begincoord, double endcoord, double value);
    int    checkFields();
    void   initiateThermoPhysicalProperties(double cpinput, double cvinput);    
    void   updateThermoPhysicalProperties();
    void   updateBoundaryConditions();
    
    // Access to variables

    void   getRho(      double* destination );
    void   getRhoU(     double* destination ); 
    void   getRhoE(     double* destination );
    void   getRhoFlux(  double* destination );
    void   getRhoUFlux( double* destination );
    void   getRhoEFlux( double* destination );

    void   updateRho(   double* origin );
    void   updateU(     double* origin ); 
    void   updateE(     double* origin );

    int    getNumberofPoints();
    double getDelta();

    void   printVTK(double timestep);

};