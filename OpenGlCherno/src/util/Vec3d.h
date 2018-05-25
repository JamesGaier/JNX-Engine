#ifndef _VEC3D
#define _VEC3D

#include <iostream>
#include <glm/glm.hpp>

class Vec3d {
private:
	double x, y, z;
public:
	Vec3d(double x, double y, double z);
	Vec3d(double all); // Set all to the same value
	Vec3d(); //Zero vector
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
	operator glm::vec3() const;
};
//Other Math
Vec3d operator*(const double& lhs, const Vec3d& rhs);

//Input and Output
std::ostream& operator<<(std::ostream& output, const Vec3d& rhs);
std::istream& operator>>(std::istream& input, Vec3d& rhs);

#endif