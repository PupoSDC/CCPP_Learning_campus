#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class Mesh {

	double              totalsize;
	double              firstcoordinate;
	double				delta;
	int                 numberofpoints;

	vector<double> *points;
	vector<double> *U;
	vector<double> *E;
	vector<double> *T;
	vector<double> *p;
	vector<double> *rho;
	vector<double> *macno;  // Mac number

	double k;               // c_p /c_v = const
	double cv;              // C_v  [kJ/kg.K]
	double cp;              // C_ p [kJ/kg.K]

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