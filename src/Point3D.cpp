#include <iostream>
#include <cmath>
#include "Point3D.h"

using namespace std;

double Point3D::getX(){
	return this->x;
}

double Point3D::getY(){
	return this->y;
}

double Point3D::getZ(){
	return this->z;
}

void Point3D::setX(double x){
	this->x = x;
}

void Point3D::setY(double y){
	this->y = y;
}

void Point3D::setZ(double z){
	this->z = z;
}

ostream& operator<<(ostream& o, Point3D p){
	o << "(" << p.x << ", " << p.y << ", " << p.z << ")";
	return o;
}

Point3D Point3D::operator+(Point3D b){
	Point3D p = Point3D();
	p.x = this->x + b.x;
	p.y = this->y + b.y;
	p.z = this->z + b.z;
	return p;
}

Point3D operator*(double k, Point3D b){
	Point3D p;
	p.setX(k * b.getX());
	p.setY(k * b.getY());
	p.setZ(k * b.getZ());
	return p;
}

Point3D operator*(Point3D b, double k){
	Point3D p;
	p.setX(k * b.getX());
	p.setY(k * b.getY());
	p.setZ(k * b.getZ());
	return p;
}

Point3D operator/(Point3D b, double k){
	Point3D p;
	p.setX(b.getX() / k);
	p.setY(b.getY() / k);
	p.setZ(b.getZ() / k);
	return p;
}

Point3D Point3D::dotProduct(Point3D b){
	Point3D p;
	p.x = this->x * b.x;
	p.y = this->y * b.y;
	p.z = this->z * b.z;
	return p;
}

Point3D Point3D::crossProduct(Point3D b){
	Point3D p;
	p.x = this->y * b.z - this->z * b.y;
	p.y = this->z * b.x - this->x * b.z;
	p.z = this->x * b.y - this->y * b.x;
	return p;
}

double Point3D::norm(){
	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}
