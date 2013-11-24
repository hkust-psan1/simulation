#ifndef __Simulation__material__
#define __Simulation__material__

#include "vec3.h"

class Material {
public:
	Material(const std::string& n);
    float ke;  // emissive
    Vec3 ka;  // ambient
    Vec3 ks;  // specular
    Vec3 kd;  // diffuse
	bool isTransmissive;
    
    std::string name;
    
    float ior;
	float ior_inverse;
    float refractFactor;
    float refractGloss;
    float reflectFactor;
    float reflectGloss;
    float subsurfScatterScale;
};

#endif /* defined(__Simulation__material__) */
