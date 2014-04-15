#ifndef __POINT3D_H_INCLUDED__
#define __POINT3D_H_INCLUDED__

#include <iostream>

using namespace std;


class Point3D
{
private:
	double x,y,z;
public:
	// Constructors
	Point3D(double a = 0, double b = 0, double c = 0)
	{
		x = a;
		y = b;
		z = c;
	}
	// Getters and Setters
	double getX();
	double getY();
	double getZ();
	void setX(double);
	void setY(double);
	void setZ(double);
	// Methods
	friend std::ostream& ::operator<<(std::ostream&, Point3D); 
	Point3D operator+(Point3D);
	Point3D dotProduct(Point3D);
	Point3D crossProduct(Point3D);
	double norm();
};

Point3D operator*(double, Point3D);
Point3D operator*(Point3D, double);
Point3D operator/(Point3D, double);

#endif // _POINT3D_H_INCLUDED__
