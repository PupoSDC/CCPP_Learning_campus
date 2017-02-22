#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include "cell.h"


class Mesh {

	class Mesh_Cell: public Cell {

		double coordinate_x;
		double coordinate_y;
		double coordinate_z;

		double size_x;
		double size_y;
		double size_z;

		Mesh_Cell *neighboor_above;
		Mesh_Cell *neighboor_below;
		Mesh_Cell *neighboor_right;
		Mesh_Cell *neighboor_left;
		Mesh_Cell *neighboor_front;
		Mesh_Cell *neighboor_back;

		public:

			inline double getCoordinate_x(){ return coordinate_x; };
			inline double getCoordinate_y(){ return coordinate_y; };
			inline double getCoordinate_z(){ return coordinate_z; };
			inline double getSize_x(){ return size_x; };
			inline double getSize_y(){ return size_y; };
			inline double getSize_z(){ return size_z; };

			double getVolume();	
	};

	std::vector<Mesh_Cell*>  Cells;

public:

	Mesh();

};