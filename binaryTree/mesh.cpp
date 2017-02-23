/*
#include "mesh.h"

///////////////////////////////////////////////////////////////////////////////////
////// Operators for subclass Mesh_Cell ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


Mesh::Mesh_Cell::Mesh_Cell(
	double input_coordinate_x, double input_coordinate_y, double input_coordinate_z,
    double input_size_x,       double input_size_y,       double input_size_z ){

	constructor(
		input_coordinate_x, input_coordinate_y, input_coordinate_z,
		input_size_x,       input_size_y,       input_size_z);
}

///////////////////////////////////////////////////////////////////////////////////
////// Operators for Mesh class ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

Mesh::Mesh(double size, size_t input_number_of_cells){

	number_of_cells = input_number_of_cells;

	cells.resize(number_of_cells);

	double delta_x = size/number_of_cells;

	// Creates a cubic cell of size delta_x for the entire mesh
	for( int i = 0; i < number_of_cells; i++ ){

		cells[i][0].resize(1);
		cells[i][0][0] = new Mesh_Cell( 
			delta_x/2 + delta_x * i,    // x coordinate
			0,                          // y coordinate
			0,                          // z coordinate
			delta_x,                    // Size of cell in x direction
			delta_x,                    // Size of cell in y direction
			delta_x                     // Size of cell in z direction
		);
	}
}


void Mesh::printVTK(string flag){

    string filename;

    filename = "results_ " + flag +  ".vtk";
    ofstream myfile (filename);

    if (myfile.is_open())
    {
        myfile << "# vtk DataFile Version 3.1 \n"
               << "ASCII \n"
               << "DATASET UNSTRUCTURED_GRID\n";

        myfile << "\n\nPOINTS " << number_of_cells <<" FLOAT\n";

        for (int i = 0; i< cells.size(); i++)
        {
            myfile << points[i] << "   0 0\n"
                   << points[i] << " 0.2 0\n";
        }

        myfile << "\n\nCELLS " << cells.size() -1 <<" " << 5*(cells.size() -1) << "\n";     

        for (int i = 0; i<cells.size()-1; i++)
        {
            myfile << "4 " << 2*i << " " << 2*(i+1) << " " << 2*(i+1) +1 << " " << 2*i+1 << "\n";
        }

        myfile << "\n\nCELL_TYPES " << cells.size() -1 << "\n";   
        
        for (int i = 0; i<cells.size()-1; i++)
        {
            myfile << "9 ";
        }

        /*
        myfile << "\n\n\nPOINT_DATA " << 2*cells.size() << "\n";

        for (int j = 0; j<nofvectorstoprint; j++)
        {
            
            myfile << "SCALARS " << vectornames[j] << " FLOAT\n"
                   << "LOOKUP_TABLE default\n";

            for (int i = 0; i<cells.size(); i++)
            {
                myfile << vectorstoprint[j][i] << "\n";
                myfile << vectorstoprint[j][i] << "\n";
            }   

            myfile << "\n\n";   
        }
		*/
/*
        myfile.close();
    }
    else cout << "Unable to open file";
} */