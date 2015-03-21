/*
 * Matrix3d.h
 *
 *  Created on: 27-Apr-2014
 *      Author: jaideep
 */

#ifndef MATRIX3D_H_
#define MATRIX3D_H_

#include "Eigen/Dense"

namespace solid
{
	namespace core
	{
		class Matrix3d : public Eigen::Matrix3d
		{
		public:
			Matrix3d()
			{
			}
			;
			Matrix3d(const Eigen::Matrix3d& mat) :
					Eigen::Matrix3d(mat)
			{
			}
			;
			virtual ~Matrix3d()
			{
			}
			;
			Matrix3d& operator=(const Eigen::Matrix3d& rhs);
		};

	} /* namespace core */
} /* namespace solid */
#endif /* MATRIX3D_H_ */
