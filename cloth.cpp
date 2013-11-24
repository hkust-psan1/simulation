#include "cloth.h"

Cloth::Cloth(int s) : size(s) {
    gridLength = 1.0 / size;
    springCoeff = 10;
    
    vertices = new Vec3*[size];
    forces = new Vec3*[size];
    speeds = new Vec3*[size];
    
    for (int i = 0; i < size; i++) {
        vertices[i] = new Vec3[size];
        forces[i] = new Vec3[size];
        speeds[i] = new Vec3[size];

        for (int j = 0; j < size; j++) {
            // vertices[i][j] = Vec3(-0.5 + gridLength * i, -0.5 + gridLength * j, 0);
            vertices[i][j] = Vec3(-0.5 + gridLength * i, 0, -0.5 + gridLength * j);
            forces[i][j] = Vec3(0, 0, 0);
            speeds[i][j] = Vec3(0, 0, 0);
        }
    }
    
}

Cloth::~Cloth() {
    
}

void Cloth::simulate() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Vec3 v = vertices[i][j];
            forces[i][j].x = 0;
            forces[i][j].y = -0.01;
            forces[i][j].z = 0;
            
            for (IndexPair ip : getNeighbors(i, j)) {
                double origLength = sqrt((ip.i - i) * (ip.i - i) + (ip.j - j) * (ip.j - j)) * gridLength;
                Vec3 d = vertices[ip.i][ip.j] - v;
                forces[i][j] += springCoeff * (d.length() - origLength) * d;
            }
            
            forces[i][j] += speeds[i][j] * (-0.01);
        }
    }
    
    forces[0][size - 1].x = 0;
    forces[0][size - 1].y = 0;
    forces[0][size - 1].z = 0;
    forces[size - 1][size - 1].x = 0;
    forces[size - 1][size - 1].y = 0;
    forces[size - 1][size - 1].z = 0;
    forces[0][0].x = 0;
    forces[0][0].y = 0;
    forces[0][0].z = 0;
    forces[size - 1][0].x = 0;
    forces[size - 1][0].y = 0;
    forces[size - 1][0].z = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            speeds[i][j] += forces[i][j];
            vertices[i][j] += speeds[i][j] * 0.01;
        }
    }
}

vector<Vec3> Cloth::getStructuralNeighbors(int i, int j) {
    vector<Vec3> neighbors;

    if (i > 0) {
        neighbors.push_back(vertices[i - 1][j]);
    }
    
    if (j > 0) {
        neighbors.push_back(vertices[i][j - 1]);
    }
    
    if (i < size - 1) {
        neighbors.push_back(vertices[i + 1][j]);
    }
    
    if (j < size - 1) {
        neighbors.push_back(vertices[i][j + 1]);
    }

    return neighbors;
}

vector<Vec3> Cloth::getSheerNeighbors(int i, int j) {
    vector<Vec3> neighbors;
    
    if (i > 0 && j > 0) {
        neighbors.push_back(vertices[i - 1][j - 1]);
    }
    
    if (i < size - 1 && j > 0) {
        neighbors.push_back(vertices[i + 1][j - 1]);
    }
    
    if (i > 0 && j < size - 1) {
        neighbors.push_back(vertices[i - 1][j + 1]);
    }
    
    if (i < size - 1 && j < size - 1) {
        neighbors.push_back(vertices[i + 1][j + 1]);
    }
    
    return neighbors;
}

vector<Vec3> Cloth::getBendingNeighbors(int i, int j) {
    vector<Vec3> neighbors;
    
    for (int ii = i - 2; ii <= i + 2; ii++) {
        for (int jj = j - 2; jj <= j + 2; jj++) {
            if (ii >= 0 && ii < size && jj >= 0 && jj < size && (ii != i || jj != j)) {
                neighbors.push_back(vertices[ii][jj]);
            }
        }
    }
    
    return neighbors;
}

vector<IndexPair> Cloth::getNeighbors(int i, int j) {
    vector<IndexPair> neighbors;
    
    for (int ii = i - 2; ii <= i + 2; ii++) {
        for (int jj = j - 2; jj <= j + 2; jj++) {
            if (ii >= 0 && ii < size && jj >= 0 && jj < size && (ii != i || jj != j)) {
                neighbors.push_back({ ii, jj });
            }
        }
    }
    return neighbors;
}

Gel::Gel(int s) : size(s) {
    gridLength = 1.0 / size;
    springCoeff = 200;
    
    vertices = new Vec3**[size];
    forces = new Vec3**[size];
    speeds = new Vec3**[size];
    
    for (int i = 0; i < size; i++) {
        vertices[i] = new Vec3*[size];
        forces[i] = new Vec3*[size];
        speeds[i] = new Vec3*[size];
        
        for (int j = 0; j < size; j++) {
            vertices[i][j] = new Vec3[size];
            forces[i][j] = new Vec3[size];
            speeds[i][j] = new Vec3[size];
            
            for (int k = 0; k < size; k++) {
                vertices[i][j][k] = Vec3(-0.5 + gridLength * i, -0.5 + gridLength * j, -0.5 + gridLength * k);
                forces[i][j][k] = Vec3(0, 0, 0);
                speeds[i][j][k] = Vec3(0, 0, 0);
            }
        }
    }
}

Gel::~Gel() {
    
}

void Gel::simulate() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                Vec3 v = vertices[i][j][k];
                forces[i][j][k].x = 0;
                forces[i][j][k].y = -0.8;
                forces[i][j][k].z = 0;
                
                for (IndexTri it : getNeighbors(i, j, k)) {
                    double origLength = sqrt((it.i - i) * (it.i - i) +
                            (it.j - j) * (it.j - j) + (it.k - k) * (it.k - k)) * gridLength;
                    Vec3 d = vertices[it.i][it.j][it.k] - v;
                    forces[i][j][k] += springCoeff * (d.length() - origLength) * d;
                }
                
                forces[i][j][k] += speeds[i][j][k] * (-0.2);
            }
        }
    }

    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            forces[i][0][k].y = 0;
        }
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                speeds[i][j][k] += forces[i][j][k] * 0.01;
                vertices[i][j][k] += speeds[i][j][k] * 0.01;
            }
        }
    }
    /*
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Vec3 v = vertices[i][j];
            forces[i][j].x = 0;
            forces[i][j].y = -0.01;
            forces[i][j].z = 0;
            
            for (IndexPair ip : getNeighbors(i, j)) {
                double origLength = sqrt((ip.i - i) * (ip.i - i) + (ip.j - j) * (ip.j - j)) * gridLength;
                Vec3 d = vertices[ip.i][ip.j] - v;
                forces[i][j] += springCoeff * (d.length() - origLength) * d;
            }
            
            forces[i][j] += speeds[i][j] * (-0.01);
        }
    }
    
    forces[0][size - 1].x = 0;
    forces[0][size - 1].y = 0;
    forces[0][size - 1].z = 0;
    forces[size - 1][size - 1].x = 0;
    forces[size - 1][size - 1].y = 0;
    forces[size - 1][size - 1].z = 0;
    forces[0][0].x = 0;
    forces[0][0].y = 0;
    forces[0][0].z = 0;
    forces[size - 1][0].x = 0;
    forces[size - 1][0].y = 0;
    forces[size - 1][0].z = 0;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            speeds[i][j] += forces[i][j];
            vertices[i][j] += speeds[i][j] * 0.01;
        }
    }
    */
}

vector<IndexTri> Gel::getNeighbors(int i, int j, int k) {
    vector<IndexTri> neighbors;
    
    for (int ii = i - 2; ii <= i + 2; ii++) {
        for (int jj = j - 2; jj <= j + 2; jj++) {
            for (int kk = k - 2; kk <= k + 2; kk++) {
                if (ii >= 0 && ii < size && jj >= 0 && jj < size && kk >= 0 && kk < size &&
                        (ii != i || jj != j || kk != k)) {
                    neighbors.push_back({ ii, jj, kk });
                }
            }
        }
    }
    return neighbors;
}