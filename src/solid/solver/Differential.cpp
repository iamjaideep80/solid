/*
 * Differential.cpp
 *
 *  Created on: 10-May-2014
 *      Author: jaideep
 */

#include "Differential.h"

namespace solid
{
	namespace solver
	{

		Differential::Differential(solid::core::RigidBody* rbdPtr) :
				rbdPtr(rbdPtr)
		{
		}

		Differential::~Differential()
		{
		}
		void Differential::operator()(state_type const &x, state_type &dxdt, double t) const
		{
			solid::core::Quaternion omegaQuat(0, rbdPtr->angularVelocity[0] * t,
												rbdPtr->angularVelocity[1] * t,
												rbdPtr->angularVelocity[2] * t);
			solid::core::Quaternion qdot = omegaQuat * rbdPtr->rotationQuaternion * 0.5;

			dxdt[0] = x[7] / rbdPtr->mass;
			dxdt[1] = x[8] / rbdPtr->mass;
			dxdt[2] = x[9] / rbdPtr->mass;
			dxdt[3] = qdot.w();
			dxdt[4] = qdot.x();
			dxdt[5] = qdot.y();
			dxdt[6] = qdot.z();
			dxdt[7] = rbdPtr->force[0];
			dxdt[8] = rbdPtr->force[1];
			dxdt[9] = rbdPtr->force[2];
			dxdt[10] = rbdPtr->torque[0];
			dxdt[11] = rbdPtr->torque[1];
			dxdt[12] = rbdPtr->torque[2];
		}

	} /* namespace solver */
} /* namespace solid */
