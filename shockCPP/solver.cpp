#include "solver.h"

Solver::Solver( Mesh &mesh, void( Mesh::*getFieldValuesAndCopyTo)( double* ), void( Mesh::*getFluxValuesAndCopyTo )( double* ) ){

    numberofpoints = mesh.getNumberofPoints();

    U       = new double[numberofpoints];
    Uflux   = new double[numberofpoints];
    Uplus   = new double[numberofpoints]; 

    //matrixA = new double*[numberofpoints];
    //for(int i=0; i<numberofpoints; i++)
    //{
    //	matrixA[i] = new double[numberofpoints];
    //}

    //vectorB = new double[numberofpoints];

    deltaX  = mesh.getDelta();

    (mesh.*getFieldValuesAndCopyTo)(U); 
    (mesh.*getFluxValuesAndCopyTo )(Uflux);
};

void Solver::advanceTime(double deltaTinput){
	deltaT = deltaTinput;

	for(int i=1; i<numberofpoints-1; i++)
    {
    	U[i] = Uplus[i];

    }

	simpleUpwindScheme();
}

void Solver::simpleUpwindScheme(){

	for(int i=1; i<numberofpoints-1; i++)
    {	
		Uplus[i] = U[i];

		if( Uflux > 0)
		{
			Uplus[i] += (deltaX / deltaT) * ( Uflux[i] - Uflux[i-1] );
		}
		else if (Uflux < 0)
		{
			Uplus[i] += (deltaX / deltaT) * ( Uflux[i+1] - Uflux[i] );
		}
 	
    }
}
