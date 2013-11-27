#ifndef __Simulation__cloth__
#define __Simulation__cloth__

#include "particle.h"

class Spring;
class Gel;

class Particle {
public:
    Particle(const Vec3& p, double r, Gel* c);
    
    inline void addSpring(Spring* s) {
        springs.push_back(s);
    }
    
    inline void setIndex(int i, int j, int k) {
        this->i = i;
        this->j = j;
        this->k = k;
    }
    
    inline void resetForce() {
        force.x = 0;
        force.y = 0;
        force.z = 0;
    }
    
    inline void addForce(const Vec3& f) {
        force += f;
    }
    
    void updateForce();
    void updatePos(double deltaT);
    
    Vec3 pos;
    Vec3 speed;
    Vec3 force;
    
    double radius;
    double mass;
    int i, j, k;
    
    Gel* parent;
    
    vector<Spring*> springs; // springs connected to this particle
    
    bool atBottom;
private:
    static const Vec3 gravity;
};

class Spring {
public:
    Spring(Particle* p1, Particle* p2);
    ~Spring();
    
    void update();
    
    bool broken;
private:
    Particle* p1;
    Particle* p2;
    
    double origLength;
    double springCoeff;
};

class IndexTri {
public:
    IndexTri(int i, int j, int k) {
        this->i = i;
        this->j = j;
        this->k = k;
    }
    
    friend bool operator<(const IndexTri& t1, const IndexTri& t2) {
        if (t1.i == t2.i) {
            if (t1.j == t2.j) {
                if (t1.k == t2.k) {
                    return 0;
                }
                return t1.k - t2.k;
            }
            return t1.j - t2.j;
        }
        return t1.i - t2.i;
    }
    
    int i;
    int j;
    int k;
};

class GelFace {
public:
    inline void addParticle(Particle* p) {
        vertices.push_back(p);
    }
    vector<Particle*> vertices;
};

class Gel {
public:
    Gel(int s, double l = 1, const Vec3& c = Vec3(0, 0, 0));
    ~Gel();

    void simulate();
    
    void clearState();
    
    void draw();
    
    int size;
    double length;
    
    Vec3 center;
    
    Vec3*** vertices;
    Vec3*** forces;
    Vec3*** speeds;
    
    bool still;
    
    vector<Particle*> particles;
    vector<Spring*> springs;
    vector<GelFace*> faces;
    
    // map<IndexTri, Particle*> indexParticleMap;
    
    static vector<Particle*> allParticles;
    
    Particle**** displayParticles;
private:
    vector<IndexTri> getNeighbors(int i, int j, int k);
    
    double gridLength;
};

#endif /* defined(__Simulation__cloth__) */
