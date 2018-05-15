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
	return *this + (rhs*-1);
}

Vec3d Vec3d::operator*(const double& rhs) const {
	return Vec3d(this->x*rhs, this->y*rhs, this->z*rhs);
}

Vec3d Vec3d::operator/(const double& rhs) const {
	return this->operator*(1 / rhs);
}

std::ostream & operator<<(std::ostream & out, const Vec3d & rhs) {
	out << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
	return out;
}
