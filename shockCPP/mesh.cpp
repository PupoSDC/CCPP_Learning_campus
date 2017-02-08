#include "mesh.h"

Mesh::Mesh(double meshbegin, double meshend, int numberofmeshpoints)
{
	numberofpoints  = numberofmeshpoints;
	totalsize       = meshend-meshbegin;
	firstcoordinate = meshbegin; 
	delta           = totalsize/(numberofpoints - 1);
	
	boundaryset    = false;
	propertiesset  = false;

	
	points  = new vector<double>(numberofmeshpoints); 
  	U       = new vector<double>(numberofmeshpoints); 
	E       = new vector<double>(numberofmeshpoints); 
	T       = new vector<double>(numberofmeshpoints);
	p       = new vector<double>(numberofmeshpoints); 
	rho     = new vector<double>(numberofmeshpoints);
	
	for( int i = 0; i < numberofpoints; i++)
	{
		(*points)[i] = meshbegin + delta * i;
	}
}

void Mesh::setField(string field, double begincoord, double endcoord, double value)
{
	// Fills a field with a "value" from "begincoord" to "endcoord"
	
	vector<double> *vectortofill;

	     if(field == "velocity"     ){ vectortofill = U; }
	else if(field == "temperature"  ){ vectortofill = E; }
	else if(field == "pressure"     ){ vectortofill = p; }
	else
	{
		cout << "An error as occured creating a field. Field " << field << " does not exist!\n";
		return;
	}

	if( begincoord < firstcoordinate || endcoord > (firstcoordinate + totalsize) )
	{
		cout << "An error as occured creating a field. Field " << field << " is out of bounds!\n";
		return;		
	}

	for( int i = 0; i < numberofpoints; i++)
	{
		if ( (*points)[i] > begincoord || (*points)[i] <= endcoord )
		{
			(*vectortofill)[i] = value;	
		}	
	}
}

int Mesh::checkFields()
{
	// Checks if all fields have been filled; Returns -1 in case of error.

	bool error = false;

	cout << "\nChecking initial field\n";
	cout.precision(3);

	for( int i = 0; i < numberofpoints; i++)
	{
		if ( !(*U)[i] )
		{
			cout << "    Velocity    is undefined for point" << std::setw(4) << i <<", coordinate" << std::setw(4) << (*points)[i] << "!\n";
			error = true;
		}
		if ( !(*E)[i] )
		{
			cout << "    Temperature is undefined for point"<< std::setw(4) << i <<", coordinate" << std::setw(4) << (*points)[i] << "!\n";
			error = true;
		}
		if ( !(*p)[i] )
		{
			cout << "    Pressure    is undefined for point"<< std::setw(4) << i <<", coordinate" << std::setw(4) << (*points)[i] << "!\n";
			error = true;
		}		
	}

	if(error)
	{
		return -1; 
	} 
	else     
	{ 
		cout << "OK! \n";
		return  0; 
	}
}

void Mesh::printVTK()
{
	
}