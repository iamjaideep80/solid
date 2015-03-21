/*
 * Vector3d.cpp
 *
 *  Created on: 27-Apr-2014
 *      Author: jaideep
 */

#include "Vector3d.h"
#include <iostream>

namespace solid
{
	namespace core
	{
		void Vector3d::assign(double value0, double value1, double value2)
		{
			col(0) = Vector3d(value0, value1, value2);
		}
		Vector3d& Vector3d::operator=(const Eigen::Vector3d& rhs)
		{
			assign((double) rhs[0], (double) rhs[1], (double) rhs[2]);
			return *this;
		}

//		Vector3d& Vector3d::operator-(const Vector3d& other)
//		{
//			Vector3d temp;
//			temp[0] = col(0)[0] - other[0];
//			temp[1] = col(0)[1] - other[1];
//			temp[2] = col(0)[2] - other[2];
//			return temp;
//		}

	} /* namespace core */
} /* namespace solid */
