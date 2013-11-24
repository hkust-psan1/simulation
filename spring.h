#ifndef __Simulation__spring__
#define __Simulation__spring__

#include "particle.h"

class Spring {
public:
    Spring(Particle* p1, Particle* p2);
    ~Spring();
    
    // get the other end at a spring
    /*
    inline Particle* otherEnd(Particle* p) {
        return p == particles[0] ? particles[1] : particles[0];
    }
    */
private:
    Particle* particles[2]; // particles at the ends of the spring
};

#endif /* defined(__Simulation__spring__) */
