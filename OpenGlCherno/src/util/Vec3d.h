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
	
	//Accessor
	double operator[](const int& rhs) const;
};
//Other Math
Vec3d operator*(const double& lhs, const Vec3d& rhs);

//Input and Output
std::ostream& operator<<(std::ostream& output, const Vec3d& rhs);
std::istream& operator>>(std::istream& input, Vec3d& rhs);

#endif