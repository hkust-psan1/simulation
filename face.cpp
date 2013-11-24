#include "face.h"
#define EPSILON 0.00001

void Face::calculateFaceNormal() {
    e1 = vertices[1]->pos - vertices[0]->pos;
    e2 = vertices[2]->pos - vertices[0]->pos;
    normal = cross(e1, e2);
    normal.normalize();
}

Vec3 Face::getRandomPos() {
    float r1 = (float)rand() / (float)RAND_MAX;
    float r2 = (float)rand() / (float)RAND_MAX;
    
    return vertices[0]->pos + e1 * r1 + e2 * r2;
}

bool twoFaceIntersect(const Face& f1, const Face& f2) {
    
    return false;
}