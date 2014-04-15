#include "Point3D.h"
#include <iostream>

using namespace std;

int main(){
	Point3D q(1,1,1), r(2,3,4), p;
	p = q.crossProduct(r);
	p = r;
	cout << p.getX() << " " << p.getY() << " " << p.getZ() << endl;
	cout << q.norm() << endl;
	cout << 3 * p << endl;
	cout << q / 3.5 << endl;
	cout << q * 3.0001 << endl;
}
