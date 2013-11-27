#include "spring.h"

/*
Spring::Spring(Particle* p1, Particle* p2) {
    this->p1 = p1;
    this->p2 = p2;
    
    p1->addSpring(this);
    p2->addSpring(this);
    
    origLength = (p1->pos - p2->pos).length();
}

Spring::~Spring() {
}

void Spring::update(double deltaT) {
    double lengthDiff = (p1->pos - p2->pos).length() - origLength;
    p1->addForce(lengthDiff * (p2 - p1));
    p2->addForce(lengthDiff * (p1 - p2));
}
*/