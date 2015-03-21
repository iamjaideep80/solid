#include "Eigen/Geometry"
#include "Eigen/Dense"

#include <iostream.h>
#include "../core/Quaternion.h"
int main()
{
	Eigen::Vector3d axis(0, 1, 0);
	Eigen::Quaternion<double> q;
	q = Eigen::AngleAxis<double>(0.17453, axis);
	std::cout << q.w() << "	" << q.x() << "	" << q.y() << "	" << q.z() << std::endl;

	solid::core::Quaternion a(41, 14, 24, 43);
	solid::core::Quaternion b(44, 42, 41, 40);
	solid::core::Quaternion c(0.1, 0.2, 0.3, 0.4);
	c = a + b;
	std::cout << "c : " << c << std::endl;

	return 0;
}
