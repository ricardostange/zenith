#include <iostream>
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

Point3D Point3D::operator+(Point3D b){
	Point3D p = Point3D();
	p.x = this->x + b.getX();
	p.y = this->y + b.getY();
	p.z = this->z + b.getZ();
	return p;
}
