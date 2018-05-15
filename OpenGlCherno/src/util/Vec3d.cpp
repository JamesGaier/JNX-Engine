#include "Vec3d.h"
#include <iostream>
#include <cmath>

Vec3d::Vec3d(double x, double y, double z) {
	setX(x);
	setY(y);
	setZ(z);
}

Vec3d::Vec3d(const Vec3d & copy) {
	Vec3d(copy.x, copy.y, copy.z);
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
	return this->x*this->x + this->y*this->y + this->z*this->z;
}

Vec3d Vec3d::normalized() const {
	return this->operator/(sqrt(this->magnitudeSquared()));
}

Vec3d Vec3d::operator+(const Vec3d & rhs) const {
	return Vec3d(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vec3d Vec3d::operator-(const Vec3d & rhs) const {
	return *this + (-1 * rhs);
}

Vec3d Vec3d::operator*(const double& rhs) const {
	return Vec3d(this->x*rhs, this->y*rhs, this->z*rhs);
}

Vec3d Vec3d::operator/(const double& rhs) const {
	return (*this)*(1 / rhs);
}

//Array {x, y, z}
double Vec3d::operator[](const int & rhs) const {
	switch(rhs) {
		case 0:return x;
		case 1: return y;
		case 2:return z;
		default:
			return -1;
	}
}

Vec3d operator*(const double & lhs, const Vec3d & rhs) {
	return rhs * lhs;
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
