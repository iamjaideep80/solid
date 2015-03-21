/*
 * Matrix3d.cpp
 *
 *  Created on: 27-Apr-2014
 *      Author: jaideep
 */

#include "Matrix3d.h"

namespace solid
{
	namespace core
	{
		Matrix3d& Matrix3d::operator=(const Eigen::Matrix3d& rhs)
		{
			col(0) = rhs.col(0);
			col(1) = rhs.col(1);
			col(2) = rhs.col(2);
			return *this;
		}
	} /* namespace core */
} /* namespace solid */
