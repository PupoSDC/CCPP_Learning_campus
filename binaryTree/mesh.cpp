#include "mesh.h"

double Mesh::Mesh_Cell::getVolume(){
	// Currently only considers parallepipidic cells
	return size_x * size_y * size_z;
}

Mesh::Mesh(){

	
}