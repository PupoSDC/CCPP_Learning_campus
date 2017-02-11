#include "solver.h"

Solver::Solver( Mesh &meshobject, void( Mesh::*getField)( double* ), void( Mesh::*getFlux)( double* ) ){

	mesh = &meshobject;

    numberofpoints = mesh->getNumberofPoints();

    U       = new double[numberofpoints];
    Uflux   = new double[numberofpoints];
    Uplus   = new double[numberofpoints]; 

    deltaX  = mesh->getDelta();

    getFieldValuesAndCopyTo = getField;
    getFluxValuesAndCopyTo  = getFlux;

    (mesh->*getFieldValuesAndCopyTo)(U); 
    (mesh->*getFluxValuesAndCopyTo )(Uflux);
};

void Solver::advanceTime(double deltaTinput){
	
	deltaT = deltaTinput;

	(mesh->*getFieldValuesAndCopyTo)(U); 
    (mesh->*getFluxValuesAndCopyTo )(Uflux);

	//simpleUpwindScheme();
	simpleCentralScheme();
}

void Solver::simpleUpwindScheme(){

	for(int i=0; i<numberofpoints; i++)
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

void Solver::simpleCentralScheme(){

	for(int i=1; i<numberofpoints-1; i++)
    {	
		Uplus[i] = U[i] - (deltaT / deltaX)*(Uflux[i+1] + Uflux[i-1])/2;  	
    }
}



double* Solver::updatedField(){ return Uplus; }

double Solver::maxCourant(){
	double Co_max = 0;

	for(int i=1; i<numberofpoints-1; i++)
    {
    	if ( abs(U[i])*deltaT/deltaX > Co_max )
    	{
    		Co_max = abs(U[i])*deltaT/deltaX; 
    	}
    }
}