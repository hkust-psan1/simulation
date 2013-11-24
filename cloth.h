#ifndef __Simulation__cloth__
#define __Simulation__cloth__

#include "vec3.h"

struct IndexPair {
    int i;
    int j;
};

struct IndexTri {
    int i;
    int j;
    int k;
};

class Cloth {
public:
    Cloth(int s);
    ~Cloth();
    void simulate();
    
    int size;

    Vec3** vertices;
    Vec3** forces;
    Vec3** speeds;    
private:
    vector<Vec3> getStructuralNeighbors(int i, int j);
    vector<Vec3> getSheerNeighbors(int i, int j);
    vector<Vec3> getBendingNeighbors(int i, int j);
    
    vector<IndexPair> getNeighbors(int i, int j);
    
    double gridLength;
    
    double springCoeff;
};

class Gel {
public:
    Gel(int s);
    ~Gel();
    void simulate();
    
    int size;
    Vec3*** vertices;
    Vec3*** forces;
    Vec3*** speeds;
    
private:
    vector<IndexTri> getNeighbors(int i, int j, int k);
    
    double gridLength;
    double springCoeff;
};

#endif /* defined(__Simulation__cloth__) */
