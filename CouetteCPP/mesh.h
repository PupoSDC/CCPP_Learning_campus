#include <vector>
#include <stdio.h>
#include <cmath>

class Mesh {

	double              height;
	double				delta;
	double              viscosity;
	
	double              time;
	double              timestep;
	double              sigma;
	double              scheme;
	double              residual;

	int                 numberofpoints;

	bool                boundaryset;
	bool                propertiesset;
	bool                timepropsset;

	std::vector<double> points;
	std::vector<double> velocity;
	std::vector<double> deltaU;
	std::vector<double> deltaUprev;
	std::vector<double> previousvelocity;

	std::vector<double> vectorB;
	
	double              matrixAdiag;
	double              matrixAdiagplus1;

public:

	Mesh(double heightinput, int numberofmeshpoints);

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

};