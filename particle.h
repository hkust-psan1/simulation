#ifndef __Simulation__particle__
#define __Simulation__particle__

#include "vec3.h"

class Spring;

class Particle {
public:
    Particle(const Vec3& p, double r);
    void addSpring(Spring* s);
    Vec3 pos;
    double radius;
    double mass;
private:
    vector<Spring*> springs; // springs connected to this particle
};

#endif /* defined(__Simulation__particle__) */
