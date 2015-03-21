/*
 * Quaternion.cpp
 *
 *  Created on: 27-Apr-2014
 *      Author: jaideep
 */

#include "Quaternion.h"

namespace solid
{
	namespace core
	{

		Quaternion::Quaternion()
		{
		}

		Quaternion::Quaternion(double w, double x, double y, double z) :
				Eigen::Quaternion<double>(w, x, y, z)
		{
		}

		Quaternion::~Quaternion()
		{
		}

		Quaternion Quaternion::operator +(const Quaternion& b)
		{
			Quaternion sum(0, 0, 0, 0);
			sum.w() = this->w() + b.w();
			sum.x() = this->x() + b.x();
			sum.y() = this->y() + b.y();
			sum.z() = this->z() + b.z();
			return sum;
		}

		Quaternion Quaternion::operator *(const double& b)
		{
			Quaternion prod(0, 0, 0, 0);
			prod.w() = this->w() * b;
			prod.x() = this->x() * b;
			prod.y() = this->y() * b;
			prod.z() = this->z() * b;
			return prod;
		}

		Quaternion Quaternion::operator *(const Quaternion& q2)
		{
			solid::core::Quaternion result;
			result.w() = this->w() * q2.w() - this->x() * q2.x() - this->y() * q2.y() - this->z() * q2.z();
			result.x() = this->w() * q2.x() + this->x() * q2.w() + this->y() * q2.z() - this->z() * q2.y();
			result.y() = this->w() * q2.y() - this->x() * q2.z() + this->y() * q2.w() + this->z() * q2.x();
			result.z() = this->w() * q2.z() + this->x() * q2.y() - this->y() * q2.x() + this->z() * q2.w();
			return result;
		}

	} /* namespace core */
} /* namespace solid */
