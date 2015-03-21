/*
 * Vector3d.h
 *
 *  Created on: 27-Apr-2014
 *      Author: jaideep
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include "Eigen/Dense"

namespace solid
{
	namespace core
	{
		class Vector3d : public Eigen::Vector3d
		{
		public:
			Vector3d()
			{
			}
			;
			Vector3d(const Eigen::Vector3d& vec) :
					Eigen::Vector3d(vec)
			{
			}
			;
			Vector3d(double a, double b, double c) :
					Eigen::Vector3d(a, b, c)
			{
			}
			;
			virtual ~Vector3d()
			{
			}
			;
			void assign(double value0, double value1, double value2);
			Vector3d& operator=(const Eigen::Vector3d& rhs);
//			Vector3d& operator-(const Vector3d& other);
		};

	} /* namespace core */
} /* namespace solid */
#endif /* VECTOR3D_H_ */
