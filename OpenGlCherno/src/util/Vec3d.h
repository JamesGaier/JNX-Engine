#ifndef _VEC3D
#define _VEC3D

#include <iostream>
#include <glm/glm.hpp>
/*
* Purpose: High precision 3d vector
* @author Nicholas Baron
*/
class Vec3d {
private:
	double x, y, z;
public:
	Vec3d(double x, double y, double z);
	Vec3d(double all = 0); // Set all to the same value
	Vec3d(const Vec3d& copy);
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	
	//Math 
	double magnitudeSquared() const;
	Vec3d normalized() const;
	
	void operator+=(const Vec3d& rhs);
	void operator-=(const Vec3d& rhs);
	void operator*=(const double& rhs);
	void operator/=(const double& rhs);
	
	//Accessor
	double operator[](const int& rhs) const;
	operator glm::vec3() const;
};
//Input and Output
std::ostream& operator<<(std::ostream& output, const Vec3d& rhs);
std::istream& operator>>(std::istream& input, Vec3d& rhs);

#endif