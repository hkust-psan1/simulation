#include "spring.h"

Spring::Spring(Particle* p1, Particle* p2) {
    particles[0] = p1;
    particles[1] = p2;
    
}

Spring::~Spring() {
}
