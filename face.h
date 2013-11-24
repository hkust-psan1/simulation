#ifndef _FACE_H
#define _FACE_H

#include "vertex.h"

class Intersection;
class Object;

class Face {
public:
	// Face();
	// inline std::vector<Vertex*> getVertices() const { return vertices; };
	inline void setObject(Object* o) { obj = o; };
	inline Object* getObject() const { return obj; };
    void calculateFaceNormal();
    /* get a random position in the face */
    Vec3 getRandomPos();
    
	friend std::ostream& operator<<(std::ostream& os, const Face& f) {
		os << "Face: " << std::endl;
		for (Vertex* v : f.vertices) {
			os << *v;
		}
        return os;
    };
    
    friend bool twoFaceIntersect(const Face& f1, const Face& f2);
    
    Vertex* vertices[3];
    Vec3 e1;
    Vec3 e2;
    
private:
    Vec3 normal;
    
    /* a pointer to the obj the face belongs to */
    Object* obj;
};

#endif