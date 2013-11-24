#ifndef __Simulation__vertex__

#include "vec3.h"

class Vec3;

class Vertex {
public:
    Vertex();
	Vertex(const Vec3& p);
    
    inline void setNormal(const Vec3& n) { normal = n; };
    inline void setTexCoords(const Vec3& t) { texCoords = t; hasTexture = true; };
    
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v) {
		os << "Vertex: " << std::endl << "Position: " << v.pos << std::endl
        << "Normal: " << v.normal << std::endl
        << "Texture: " << v.texCoords << std::endl;
		return os;
	}
    
    void printData();
    
	Vec3 pos;
	Vec3 normal;
    Vec3 tangent;
    Vec3 bitangent;
	Vec3 texCoords;
    bool hasTexture;
    
    Vec3 force;
    Vec3 speed;
};

#endif /* defined(__Simulation__vertex__) */
