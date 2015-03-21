/*
 * OdeSolver.h
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#ifndef ODESOLVER_H_
#define ODESOLVER_H_

#include "../core/CommonTypes.h"
#include "../solver/State.h"
#include "../core/RigidBody.h"
#include <boost/numeric/odeint.hpp>
#include "Differential.h"

namespace solid
{
	namespace solver
	{
		using solid::core::Scalar;
		using solid::core::Vector3d;
		using solid::core::Matrix3d;
		using solid::core::Quaternion;
		class OdeSolver
		{
		public:
			OdeSolver();
			virtual ~OdeSolver();
			void applyOde(const solid::core::Scalar timeStep, solid::core::RigidBody* rbdPtr);
			void applyOdeWM(const solid::core::Scalar dt, solid::core::RigidBody* rbdPtr);
		private:
			void convertRigidBodyToStateArray(state_type& state, solid::core::RigidBody* rbdPtr);
			void convertStateArrayToRigidBody(const state_type& state, solid::core::RigidBody* rbdPtr);
		};

	} /* namespace solver */
} /* namespace quarks */
#endif /* ODESOLVER_H_ */
