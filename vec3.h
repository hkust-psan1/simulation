#ifndef Simulation_vec3_h
#define Simulation_vec3_h

#include "includes.h"

class Vec3 {
public:
	Vec3(){x = 0; y = 0; z = 0;};
	Vec3(double x, double y, double z);
	Vec3(double f) {x = f; y = f; z = f;}
	Vec3(double c[3]);
	Vec3(const Vec3& v);
    
	inline double length() const { return sqrt(x * x + y * y + z * z); };
	void normalize();
	void clamp();
    
	Vec3& operator+=(const Vec3& v);
	Vec3& operator-=(const Vec3& v);
	Vec3& operator*=(const Vec3& v);
    
    Vec3& operator=(const Vec3& v);
    double& operator[](int n);
	double get(int n) const;
	int maxElement();
    
    void print() const;
    
	friend Vec3 operator+(const Vec3& v1, const Vec3& v2);
	friend Vec3 operator-(const Vec3& v1, const Vec3& v2);
	friend Vec3 operator*(const Vec3& v1, const Vec3& v2);
	friend Vec3 operator*(const Vec3& v1, double n);
    friend Vec3 operator/(const Vec3& v1, double n);
	friend bool operator<(const Vec3& v1, const Vec3& v2);
    friend bool operator>(const Vec3& v1, const Vec3& v2);
    
	friend double dot(const Vec3& v1, const Vec3& v2);
	friend Vec3 cross(const Vec3& v1, const Vec3& v2);
    
	friend std::ostream& operator<<(std::ostream& os, const Vec3& v);
    
    Vec3 randomize(double r);
    
	double x;
	double y;
	double z;
};


#endif
