/*
 * Quaternion.h
 *
 *  Created on: 27-Apr-2014
 *      Author: jaideep
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Eigen/Geometry"

#include <iostream>
namespace solid
{
	namespace core
	{
		class Quaternion : public Eigen::Quaternion<double>
		{
		public:
			Quaternion();
			Quaternion(double w, double x, double y, double z);
			virtual ~Quaternion();
			Quaternion operator+(const Quaternion& b);
			Quaternion operator*(const double& b);
			Quaternion operator*(const Quaternion& q2);
			friend std::ostream& operator<<(std::ostream& os, const Quaternion& q)
			{
				os << "<" << q.w() << "," << q.x() << "," << q.y() << "," << q.z() << ">";
				return os;
			}
//			friend Quaternion operator*(double scalar, const Quaternion& q)
//			{
//				return q * scalar;
//			}
		};

	} /* namespace core */
} /* namespace solid */
#endif /* QUATERNION_H_ */
