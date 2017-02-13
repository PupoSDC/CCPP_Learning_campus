#include "mesh.h"

Mesh::Mesh(double meshbegin, double meshend, int numberofmeshpoints){
    numberofpoints  = numberofmeshpoints;
    totalsize       = meshend-meshbegin;
    firstcoordinate = meshbegin; 
    delta           = totalsize/(numberofpoints - 1);
        
    points    = new double[numberofmeshpoints]; 
    U         = new double[numberofmeshpoints]; 
    E         = new double[numberofmeshpoints]; 
    rho       = new double[numberofmeshpoints];
    rhoU      = new double[numberofmeshpoints];
    rhoE      = new double[numberofmeshpoints];
    rhoFlux   = new double[numberofmeshpoints]; 
    rhoUFlux  = new double[numberofmeshpoints]; 
    rhoEFlux  = new double[numberofmeshpoints];
    p         = new double[numberofmeshpoints]; 
    T         = new double[numberofmeshpoints];
    macno     = new double[numberofmeshpoints];
    
    for( int i = 0; i < numberofpoints; i++)
    {
        points[i]  = meshbegin + delta * i;
        U[i]       = -1; 
        p[i]       = -1;
        T[i]       = -1;    
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

    if(error){ return -1; } 
    else     { cout << "OK! \n"; return  0; }
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

void Mesh::initiateVariables(double cpinput, double cvinput){
    // assuming T,p and U are defined, updates rho, E, Mac speed and transport quantaties.
    // Sets constant k,cp and cv

    cv = cvinput;
    cp = cpinput;
    k  = cp/cv;

    for (int i = 0; i<numberofpoints; i++)
    {
        E[i]     = cv * T[i] + (1/2) * pow(U[i],2);
        rho[i]   = p[i] / (k * cv * T[i]);
        macno[i] = sqrt( k * p[i] / rho[i]);
        rhoU[i]  = rho[i] * U[i];
        rhoE[i]  = rho[i] * E[i];
    }   

    updateFluxes();
}

void Mesh::updateVariables(){
    for (int i = 0; i<numberofpoints; i++)
    {
        U[i]     = rhoU[i]/rho[i];
        E[i]     = rhoE[i]/rho[i];
        T[i]     = ( E[i] - (1/2) * pow(U[i],2) )/ cv;
    }  

    updateBoundaryConditions();
    
    for (int i = 0; i<numberofpoints; i++)
    {
        macno[i] = sqrt( k * p[i] / rho[i]);
        p[i]     = ( k - 1 ) * rho[i] * ( E[i] - (1/2)*pow(U[i],2) );
    }  

    updateFluxes(); 
}

void Mesh::updateFluxes(){

    rhoFlux[0]               = 0;
    rhoFlux[numberofpoints]  = 0;
    rhoUFlux[0]              = 0;
    rhoUFlux[numberofpoints] = 0;
    rhoEFlux[0]              = 0;
    rhoEFlux[numberofpoints] = 0;

    for (int i = 1; i<numberofpoints-1; i++)
    {
        rhoFlux[i]   = ( 1/4)*rho[i]  *macno[i]  *pow( (1 + U[i]  /macno[i]  ), 2 ) * 1 / delta  
                     + (-1/4)*rho[i+1]*macno[i+1]*pow( (1 - U[i+1]/macno[i+1]), 2 ) * 1 / delta   
                     - ( 1/4)*rho[i-1]*macno[i-1]*pow( (1 + U[i-1]/macno[i-1]), 2 ) * 1 / delta  
                     - (-1/4)*rho[i]  *macno[i]  *pow( (1 - U[i]  /macno[i]  ), 2 ) * 1 / delta;  

        rhoUFlux[i]  = ( 1/4)*rho[i]  *macno[i]  *pow( (1 + U[i]  /macno[i]  ), 2 ) * (2*macno[i]/k)*  ( (k-1)/2 * U[i]   / macno[i]   + 1 ) / delta;
                     + (-1/4)*rho[i+1]*macno[i+1]*pow( (1 - U[i+1]/macno[i+1]), 2 ) * (2*macno[i+1]/k)*( (k-1)/2 * U[i+1] / macno[i+1] - 1 ) / delta;
                     - ( 1/4)*rho[i-1]*macno[i-1]*pow( (1 + U[i-1]/macno[i-1]), 2 ) * (2*macno[i-1]/k)*( (k-1)/2 * U[i-1] / macno[i-1] + 1 ) / delta;
                     - (-1/4)*rho[i]  *macno[i]  *pow( (1 - U[i]  /macno[i]  ), 2 ) * (2*macno[i]/k)*  ( (k-1)/2 * U[i]   / macno[i]   - 1 ) / delta;

        rhoEFlux[i]  = ( 1/4)*rho[i]  *macno[i]  *pow( (1 + U[i]  /macno[i]  ), 2 ) * (2*pow(macno[i  ],2)/(pow(k,2)-1)) * pow( ((k-1)/2 * U[i]   / macno[i]   + 1 ),2) / delta;
                     + (-1/4)*rho[i+1]*macno[i+1]*pow( (1 - U[i+1]/macno[i+1]), 2 ) * (2*pow(macno[i+1],2)/(pow(k,2)-1)) * pow( ((k-1)/2 * U[i+1] / macno[i+1] - 1 ),2) / delta;
                     - ( 1/4)*rho[i-1]*macno[i-1]*pow( (1 + U[i-1]/macno[i-1]), 2 ) * (2*pow(macno[i-1],2)/(pow(k,2)-1)) * pow( ((k-1)/2 * U[i-1] / macno[i-1] + 1 ),2) / delta;
                     - (-1/4)*rho[i]  *macno[i]  *pow( (1 - U[i]  /macno[i]  ), 2 ) * (2*pow(macno[i  ],2)/(pow(k,2)-1)) * pow( ((k-1)/2 * U[i]   / macno[i]   - 1 ),2) / delta;       
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

double* Mesh::getRho(){            return rho;            }
double* Mesh::getRhoU(){           return rhoU;           } 
double* Mesh::getRhoE(){           return rhoE;           } 
double* Mesh::getRhoFlux(){        return rhoFlux;        }
double* Mesh::getRhoUFlux(){       return rhoUFlux;       } 
double* Mesh::getRhoEFlux(){       return rhoEFlux;       }
double  Mesh::getk(){              return k;              }     
double  Mesh::getcv(){             return cp;             }    
double  Mesh::getcp(){             return cv;             }   
int     Mesh::getNumberofPoints(){ return numberofpoints; }
double  Mesh::getDelta(){          return delta;          }

void Mesh::printVTK(double timestep){
    // Prints the current velocity, temperature and pressure to a file 
    // using vtk file format
    // TODO: Implement timestep

    string filename;

    filename = "results_" + to_string(timestep) + ".vtk";
    ofstream myfile (filename);

    double *vectorstoprint [9] = { E,U,T,p,rho,macno,rhoFlux,rhoUFlux,rhoEFlux }; 
    string  vectornames    [9] = { "energy","Velocity", "Temperature", "Pressure","rho","macno","rhoFlux","rhoUFlux","rhoEFlux" };
    int     nofvectorstoprint  = 9;

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
