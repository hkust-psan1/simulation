#ifndef __Simulation__scene__
#define __Simulation__scene__

#include "object.h"

class Scene
{
public:
    Scene();
    
	inline vector<Object*> getObjects() const { return objects; };
    inline void addObject(Object* o) { objects.push_back(o); };
    
    inline vector<_Light*> getLights() const { return lights; };
    inline void addLight(_Light* l) { lights.push_back(l); };
	
	static Vec3 ambient;
	static void setAmbient(Vec3 a) { ambient = a; }
    
	std::vector<Object*> objects;
    std::vector<_Light*> lights;
};

#endif /* defined(__Simulation__scene__) */
