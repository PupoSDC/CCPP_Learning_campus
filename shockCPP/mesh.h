#include <vector>
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

	// Pointers to the arrays containing the system variables
	double *points; // Points of the mesh
	double *U;      // Velocity
	double *E;      // Energy
	double *T;      // Temperature
	double *p;      // Pressure
	double *rho;    // Density
	double *macno;  // Mac number

	// Static global properties of the fluid
	double k;       // c_p /c_v = const
	double cv;      // C_v  [J/kg.K]
	double cp;      // C_ p [J/kg.K]

public:

	Mesh(double meshbegin, double meshend, int numberofmeshpoints);

	void   setField(string field, double begincoord, double endcoord, double value);
	int    checkFields();
	void   initiateThermoPhysicalProperties(double cpinput, double cvinput);	
	void   updateThermoPhysicalProperties();
	

	void   printVTK(double timestep);
	
	/*
	void   setBoundaries(double speedtop, double speedbottom);
	void   setPhisicalProperties(double viscosityinput);
	void   setTimeProperties(double timestepinput, double schemeinput);

	void   advanceTime();
	void   updateResidual();

	void   constructMatrixA();
	void   constructVectorB();
	void   printMeshValues();

	double getResidual();
	double getTime();

	*/

};