#include "Eigen/Geometry"
#include "Eigen/Dense"

#include <iostream.h>

int main()
{
	Eigen::Quaternion<double> q;
	q = Eigen::AngleAxis<double>(1, Eigen::Vector3d(1,1,1));
	Eigen::Vector3d angularVelocity(0, 1, 0);
//	Eigen::Matrix3d	qMat = q.matrix();
	Eigen::Quaternion<double> angularVelQuat;
	angularVelQuat = Eigen::AngleAxis<double>(0, angularVelocity);
	Eigen::Quaternion<double> prod = q * angularVelQuat;
	std::cout << prod.w() << "	" << prod.x() << "	" << prod.y() << "	" << prod.z() << std::endl;
	return 0;
}
