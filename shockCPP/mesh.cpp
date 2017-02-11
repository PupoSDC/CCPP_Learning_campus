#include "mesh.h"

Mesh::Mesh(double meshbegin, double meshend, int numberofmeshpoints){
    numberofpoints  = numberofmeshpoints;
    totalsize       = meshend-meshbegin;
    firstcoordinate = meshbegin; 
    delta           = totalsize/(numberofpoints - 1);
        
    points  = new double[numberofmeshpoints]; //,-123456789); 
    U       = new double[numberofmeshpoints]; //,-123456789); 
    E       = new double[numberofmeshpoints]; //,-123456789); 
    rho     = new double[numberofmeshpoints]; //,-123456789);
    p       = new double[numberofmeshpoints]; //,-123456789); 
    T       = new double[numberofmeshpoints]; //,-123456789);
    macno   = new double[numberofmeshpoints]; //,-123456789);
    
    for( int i = 0; i < numberofpoints; i++)
    {
        points[i]  = meshbegin + delta * i;
        U[i]       = -1; 
        E[i]       = -1; 
        rho[i]     = -1; 
        p[i]       = -1;
        T[i]       = -1;   
        macno[i]   = -1; 
    }
}

void Mesh::setField(string field, double begincoord, double endcoord, double value){
    // Fills a field with a "value" from "begincoord" to "endcoord"
    
    double *arraytofill;

         if(field == "velocity"     ){ arraytofill = U; }
    else if(field == "temperature"  ){ arraytofill = T; }
    else if(field == "pressure"     ){ arraytofill = p; }
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
        if ( points[i] >= begincoord && points[i] <= endcoord )
        {
            arraytofill[i] = value; 
        }   
    }
}

int Mesh::checkFields(){
    // Checks if all fields have been filled; Returns -1 in case of error.

    bool error = false;

    cout << "\nChecking initial field\n";
    cout.precision(3);

    for( int i = 0; i < numberofpoints; i++)
    {
        if ( U[i] == -1 )
        {
            cout << "    Velocity    is undefined for point" << std::setw(4) << i <<", coordinate" << std::setw(4) << points[i] << "!\n";
            error = true;
        }
        if ( T[i] == -1 )
        {
            cout << "    Temperature is undefined for point"<< std::setw(4) << i <<", coordinate" << std::setw(4) << points[i] << "!\n";
            error = true;
        }
        if ( p[i] == -1 )
        {
            cout << "    Pressure    is undefined for point"<< std::setw(4) << i <<", coordinate" << std::setw(4) << points[i] << "!\n";
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

void Mesh::initiateThermoPhysicalProperties(double cpinput, double cvinput){
    // assuming T,p and U are defined, updates rho, E and Mac speed.
    // Sets constant k,cp and cv

    cv = cvinput;
    cp = cpinput;
    k  = cp/cv;

    for (int i = 0; i<numberofpoints; i++)
    {
        E[i]     = cv * T[i] + (1/2) * pow(U[i],2);
        rho[i]   = p[i] / (k * cv * T[i]);
        macno[i] = sqrt( k * p[i] / rho[i]);
    }   
}

void Mesh::updateThermoPhysicalProperties(){
    for (int i = 0; i<numberofpoints; i++)
    {
        T[i]     = ( E[i] - (1/2) * pow(U[i],2) )/ cv;
        macno[i] = sqrt( k * p[i] / rho[i]);
        p[i]     = ( k - 1 ) * rho[i] * ( E[i] - (1/2)*pow(U[i],2) );
    }   
}

void Mesh::updateBoundaryConditions(){
    U[0]                = 0.0;
    U[numberofpoints]   = 0.0;
    rho[0]              = rho[1];
    rho[numberofpoints] = rho[numberofpoints-1];
    E[0]                = E[1];
    E[numberofpoints]   = E[numberofpoints-1];  
}

void Mesh::getRho(double* destination){
    // Copys rho to a destination
    for (int i = 0; i<numberofpoints; i++)
    {
        destination[i] = rho[i];
    }  
}

void Mesh::getRhoU(double* destination){
    // Copys rho*U to a destination
    for (int i = 0; i<numberofpoints; i++)
    {
        destination[i] = rho[i]*U[i];
    }  
}

void Mesh::getRhoE(double* destination){
    // Copys rho*E to a destination
    for (int i = 0; i<numberofpoints; i++)
    {
        destination[i] = rho[i]*E[i];
    }  
}

void Mesh::getRhoFlux(double* destination){
    // Copys rho to a destination
    for (int i = 0; i<numberofpoints; i++)
    {
        destination[i] = rho[i]*U[i];
    }  
}

void Mesh::getRhoUFlux(double* destination){
    // Copys rho to a destination
    for (int i = 0; i<numberofpoints; i++)
    {
        destination[i] = rho[i]*pow(U[i],2) + p[i];
    }  
}

void Mesh::getRhoEFlux(double* destination){
    // Copys rho to a destination
    for (int i = 0; i<numberofpoints; i++)
    {
        destination[i] = rho[i]*U[i]*( E[i] + p[i]/rho[i] );
    }  
}

void Mesh::updateRho(double* origin){
    for (int i = 1; i<numberofpoints-1; i++)
    {
        rho[i] = origin[i];
    }
}

void Mesh::updateU(double* origin){
    for (int i = 1; i<numberofpoints-1; i++)
    {
        U[i] = origin[i]/rho[i];
    }
}

void Mesh::updateE(double* origin){
    for (int i = 1; i<numberofpoints-1; i++)
    {
        E[i] = origin[i]/rho[i];
    }
}

int    Mesh::getNumberofPoints(){ return numberofpoints; }
double Mesh::getDelta(){          return delta;          }

void Mesh::printVTK(double timestep){
    // Prints the current velocity, temperature and pressure to a file 
    // using vtk file format
    // TODO: Implement timestep

    string filename;

    filename = "results_" + to_string(timestep) + ".vtk";
    ofstream myfile (filename);

    double *vectorstoprint [6] = { E,U,T,p,rho,macno }; 
    string  vectornames    [6] = { "energy","Velocity", "Temperature", "Pressure","rho","macno" };
    int     nofvectorstoprint  = 6;

    if (myfile.is_open())
    {
        myfile << "# vtk DataFile Version 3.1 \n"
               << "current timestep " << timestep << " \n"
               << "ASCII \n"
               << "DATASET UNSTRUCTURED_GRID\n";

        myfile << "\n\nPOINTS " << 2*numberofpoints <<" FLOAT\n";

        for (int i = 0; i<numberofpoints; i++)
        {
            myfile << points[i] << "   0 0\n"
                   << points[i] << " 0.2 0\n";
        }

        myfile << "\n\nCELLS " << numberofpoints -1 <<" " << 5*(numberofpoints -1) << "\n";     

        for (int i = 0; i<numberofpoints-1; i++)
        {
            myfile << "4 " << 2*i << " " << 2*(i+1) << " " << 2*(i+1) +1 << " " << 2*i+1 << "\n";
        }

        myfile << "\n\nCELL_TYPES " << numberofpoints -1 << "\n";   
        
        for (int i = 0; i<numberofpoints-1; i++)
        {
            myfile << "9 ";
        }

        myfile << "\n\n\nPOINT_DATA " << 2*numberofpoints << "\n";

        for (int j = 0; j<nofvectorstoprint; j++)
        {
            
            myfile << "SCALARS " << vectornames[j] << " FLOAT\n"
                   << "LOOKUP_TABLE default\n";

            for (int i = 0; i<numberofpoints; i++)
            {
                myfile << vectorstoprint[j][i] << "\n";
                myfile << vectorstoprint[j][i] << "\n";
            }   

            myfile << "\n\n";   
        }

        myfile.close();
    }
    else cout << "Unable to open file";
}
