#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>


using namespace std;

class Mesh {

	double              totalsize;
	double              firstcoordinate;
	double				delta;

	int                 numberofpoints;

	bool                boundaryset;
	bool                propertiesset;

	vector<double> *points;
	vector<double> *U;
	vector<double> *E;
	vector<double> *T;
	vector<double> *p;
	vector<double> *rho;

public:

	Mesh(double meshbegin, double meshend, int numberofmeshpoints);

	void   setField(string field, double begincoord, double endcoord, double value);
	int    checkFields();
	void   printVTK();
	
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