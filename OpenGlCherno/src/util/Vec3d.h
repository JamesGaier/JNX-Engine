#ifndef _VEC3D
#define _VEC3D

#include <iostream>

class Vec3d {
private:
	double x, y, z;
public:
	Vec3d(double x = 0, double y = 0, double z = 0);
	Vec3d(const Vec3d& copy);
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	
	//Math 
	double magnitudeSquared() const;
	Vec3d normalized() const;
	
	Vec3d operator+(const Vec3d& rhs) const;
	Vec3d operator-(const Vec3d& rhs) const;
	Vec3d operator*(const double& rhs) const;
	Vec3d operator/(const double& rhs) const;

	//Input and Output
	friend std::ostream& operator<<(std::ostream& output, const Vec3d& rhs);
};

#endif