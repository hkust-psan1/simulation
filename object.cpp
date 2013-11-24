#include "object.h"

Object::Object() {
    // mat = new Material();
}

void Object::addFace(Face* f) {
	faces.push_back(f);
	f->setObject(this);
}

Vec3 _Light::getRandomPos() {
    Face* face = faces[rand() % faces.size()];
    return face->getRandomPos();
}

bool objectCollide(const Object* o1, const Object* o2) {
    
    return false;
}