#include <vector>
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "cell.h"


class Mesh {

	struct Point{
		double coordinate_x;
		double coordinate_y;
		double coordinate_z;
	};

	class Mesh_Cell: public Cell {

		//Points of the cell;
		std::vector< Point > Points;

		// Center of the cell
		double coordinate_x;
		double coordinate_y;
		double coordinate_z;

		public:

			// Constructor for 3D HexaHedron cells
			Mesh_Cell();

			inline double getCenterCoordinate_x(){ return coordinate_x; };
			inline double getCenterCoordinate_y(){ return coordinate_y; };
			inline double getCenterCoordinate_z(){ return coordinate_z; };
	};


	// 1 Dimensional vector with all points
	std::vector< Point* > Points;

	// 3 Dimensional Vector of cells
	std::vector< std::vector< std::vector<Mesh_Cell*> > > cells;

	int number_of_cells;
	

public:

	// 1D equally spaced mesh creation Constructor call
	Mesh(double size, size_t number_of_cells); 

	void printVTK(string flag);
};