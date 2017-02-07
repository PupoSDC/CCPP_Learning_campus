#include "mesh.h"

Mesh::Mesh(double heightinput, int numberofmeshpoints)
{
	height         = heightinput;
	numberofpoints = numberofmeshpoints;
	delta          = height/ (numberofpoints - 1);
	
	boundaryset    = false;
	propertiesset  = false;
	timepropsset   = false;

	residual       = 1;

	points.reserve(numberofmeshpoints);
	vectorB.reserve(numberofmeshpoints);
	deltaU.reserve(numberofmeshpoints);
	deltaUprev.reserve(numberofmeshpoints);
	velocity.reserve(numberofmeshpoints);
	previousvelocity.reserve(numberofmeshpoints);

	for( int i = 0; i < numberofpoints; i++)
	{
		points[i]   =  height * i / ( numberofpoints -1);
		velocity[i] = 0.0;
		deltaU[i]   = 0.0;
	}
}

void Mesh::setBoundaries(double speedbot, double speedtop)
{
	velocity[0]                = speedbot;
	velocity[numberofpoints-1] = speedtop;

	boundaryset                = true;	
}

void Mesh::setPhisicalProperties(double viscosityinput)
{
	viscosity      = viscosityinput;
	propertiesset  = true;
}

void Mesh::setTimeProperties(double timestepinput, double schemeinput)
{
	time           = 0.0;
	timestep       = timestepinput;
	scheme         = schemeinput;
	sigma          = viscosity * timestep / pow(delta,2);
	timepropsset   = true;
}


void Mesh::advanceTime()
{	
	time = time + timestep;

	printf("\nCurrent time: %4.3f, current residual: %4.3f \n", time,residual);
	
	int    iteration;
	double iterationerror;

	iterationerror = 1000;
	iteration      = 0;

	for (int i = 0; i<numberofpoints; i++)
	{	
		previousvelocity[i] = velocity[i];
	}
	
	constructMatrixA();
	constructVectorB();

	while( iterationerror > 0.001 && iteration < 5)
	{
		iteration++;
		iterationerror = 0;

		for (int i = numberofpoints-2; i > 0 ; i--)
		{	

			deltaUprev[i]   = deltaU[i];
			deltaU[i]       = ( 1 / matrixAdiag ) * ( vectorB[i] - matrixAdiagplus1 * ( deltaU[i-1] + deltaU[i+1] ) );
			iterationerror += pow( deltaU[i] - deltaUprev[i],2);
		}

		iterationerror = sqrt(iterationerror);

		printf("    - Linear solve iteration %*d error: %9.8f \n",4,iteration,iterationerror);
	}

	for (int i = 1; i < numberofpoints-1; i++)
	{	
		velocity[i]  +=  deltaU[i];
	}

	updateResidual();
}

void Mesh::updateResidual()
{
	residual = 0.0;

	for (int i = 1; i < numberofpoints-2; i++)
	{
		residual += pow( vectorB[i] - matrixAdiag * deltaU[i] - matrixAdiagplus1 * ( deltaU[i-1] + deltaU[i+1] ) , 2) ;
	}	

	residual = sqrt(residual);
}

double Mesh::getResidual()
{
	return residual;
}

double Mesh::getTime()
{
	return time;
}

void Mesh::constructMatrixA()
{
	matrixAdiag      = 1.0 + 2.0 * scheme * sigma;
	matrixAdiagplus1 = - 1.0 * sigma;
}

void Mesh::constructVectorB()
{
	vectorB[0]                = sigma * ( -2.0 * velocity[0]                + velocity[1]                );
	vectorB[numberofpoints-1] = sigma * ( -2.0 * velocity[numberofpoints-1] + velocity[numberofpoints-2] );

	for( int i = 1; i < numberofpoints-1; i++)
	{
		vectorB[i] = sigma * ( -2.0 * velocity[i] + velocity[i+1]  + velocity[i-1] );
	} 
}

void Mesh::printMeshValues()
{	
	printf("\nMesh points, velocity and deltaVelocity \n\n");

	for( int i = 0; i < numberofpoints; i++)
	{	
		printf("%*d    %4.2f    %5.4f\n",4,i,points[i],velocity[i]);
	}
	printf("\n");

}

