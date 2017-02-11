#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "mesh.h"

using namespace std;

class Solver {

    // matrix system
    int numberofpoints;  // Dimension of the vectors (n) and matrix (n*n) of the system

    double *U;           // Vector U
    double *Uflux;       // Flux from Vector U
    double *Uplus;       // Vector U in the next iteration step
    double *residual;     

    double deltaT;       // timestep
    double deltaX;       // Mesh size

    double **matrixA;
    double *vectorB;    

    void simpleUpwindScheme();

public:

    Solver( Mesh &mesh, void( Mesh::*getFieldValuesAndCopyTo)( double* ), void( Mesh::*getFluxValuesAndCopyTo )( double* ) );

    void advanceTime(double deltaT);

    void updatefield();  


};