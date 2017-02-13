#include <cmath>

using namespace std;

class Solver {
    int n;               // Dimension of the vectors (n) and matrix (n*n) of the system

    double *U;           // Vector U
    double *Uflux;       // Flux from Vector U   

    double deltaT;       // timestep
    double deltaX;       // Mesh size

public:

    Solver(double *vectorU, double *vectorUflux, int numberofpoints);

    void advanceTime(double deltaT);
};