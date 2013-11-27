#ifndef __Simulation__object__
#define __Simulation__object__

#include "face.h"
#include "material.h"
#include "cloth.h"

class Face;
class Intersection;
class BoundingBox;

class Object {
public:
	Object();
	void addFace(Face* f);
    inline string getName() const { return name; };
	inline vector<Face*> getFaces() const { return faces; };
    
    // check if object is light by its emmisive coefficient
    inline bool isLight() const { return mat->ke > 0.000001; };
    
    bool smoothShading;
	Material* mat;
    std::string materialName;
    vector<Particle*> particles;
    
    Vec3 maxPos;
    Vec3 minPos;
    
    friend bool objectCollide(const Object* o1, const Object* o2);
    
protected:
    string name;
	vector<Face*> faces;
};

class _Light : public Object {
public:
    _Light();
    inline const Vec3& getColor() const { return mat->kd; };
    
    /* get a random position in the emissive object */
    Vec3 getRandomPos();
private:
};

#endif /* defined(__Simulation__object__) */
