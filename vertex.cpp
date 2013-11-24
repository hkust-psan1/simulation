#include "vertex.h"

Vertex::Vertex() {
    
}

Vertex::Vertex(const Vec3& p)
: pos(p), hasTexture(false) {
    force = Vec3(0.f, -0.01f, 0.f);
}

/*
 Vertex::Vertex(const Vec3& p, const Vec3& n, const Vec3& t)
 : pos(p), normal(n), texCoords(t), hasTexture(true) {
 
 }
 */

void Vertex::printData() {
    
}