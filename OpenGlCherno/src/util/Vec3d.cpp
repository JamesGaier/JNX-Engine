#include "Vec3d.h"
#include <iostream>
#include <cmath>

Vec3d::Vec3d(double x, double y, double z) {
	setX(x);
	setY(y);
	setZ(z);
}

Vec3d::Vec3d(double all) {
	setX(all);
	setY(all);
	setZ(all);
}

Vec3d::Vec3d(const Vec3d & copy) {
	setX(copy.x);
	setY(copy.y);
	setZ(copy.z);
}

void Vec3d::setX(double x) {
	this->x = x;
}

void Vec3d::setY(double y) {
	this->y = y;
}

void Vec3d::setZ(double z) {
	this->z = z;
}

double Vec3d::magnitudeSquared() const {
	return x * x + y * y + z * z;
}

Vec3d Vec3d::normalized() const {
	Vec3d copy(*this);
	copy /= sqrt(magnitudeSquared());
	return copy;
}

void Vec3d::operator+=(const Vec3d & rhs) {
	double tempX = x, tempY = y, tempZ = z;

	x = tempX + rhs.x;
	y = tempY + rhs.y;
	z = tempZ + rhs.z;
}

void Vec3d::operator-=(const Vec3d & rhs) {
	Vec3d copy(rhs);
	copy *= -1;
	*this += copy;
}

void Vec3d::operator*=(const double& rhs) {
	double tempX = x, tempY = y, tempZ = z;

	x = tempX * rhs;
	y = tempY * rhs;
	z = tempZ * rhs;
}

void Vec3d::operator/=(const double& rhs) {
	(*this) *= (1 / rhs);
}

//Array {x, y, z}
double Vec3d::operator[](const int & rhs) const {
	switch(rhs) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default:
			return -1;
	}
}

Vec3d::operator glm::vec3() const {
	return glm::vec3(x, y, z);
}

std::ostream & operator<<(std::ostream & out, const Vec3d & rhs) {
	out << "(" << rhs[0] << ", " << rhs[1] << ", " << rhs[2] << ")";
	return out;
}

std::istream & operator>>(std::istream & input, Vec3d & rhs) {
	double value;
	input >> value;
	rhs.setX(value);

	input >> value;
	rhs.setY(value);

	input >> value;
	rhs.setZ(value);

	return input;
}
