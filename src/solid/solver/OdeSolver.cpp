/*
 * OdeSolver.cpp
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#include "OdeSolver.h"
#include "../core/CommonTypes.h"

namespace solid
{
	namespace solver
	{
		OdeSolver::OdeSolver()
		{
		}

		OdeSolver::~OdeSolver()
		{
		}
		static
		void observer(const state_type& x, const double t)
		{
		}

		void OdeSolver::convertRigidBodyToStateArray(state_type& state, solid::core::RigidBody* rbdPtr)
		{
			state[0] = rbdPtr->translation[0];
			state[1] = rbdPtr->translation[1];
			state[2] = rbdPtr->translation[2];
			state[3] = rbdPtr->rotationQuaternion.w();
			state[4] = rbdPtr->rotationQuaternion.x();
			state[5] = rbdPtr->rotationQuaternion.y();
			state[6] = rbdPtr->rotationQuaternion.z();
			state[7] = rbdPtr->linearMomentum[0];
			state[8] = rbdPtr->linearMomentum[1];
			state[9] = rbdPtr->linearMomentum[2];
			state[10] = rbdPtr->angularMomentum[0];
			state[11] = rbdPtr->angularMomentum[1];
			state[12] = rbdPtr->angularMomentum[2];
		}

		void OdeSolver::convertStateArrayToRigidBody(const state_type& state, solid::core::RigidBody* rbdPtr)
		{
			rbdPtr->translation.assign(state[0], state[1], state[2]);

			rbdPtr->rotationQuaternion = solid::core::Quaternion(state[3], state[4], state[5], state[6]);
			rbdPtr->rotationQuaternion.normalize();

			rbdPtr->linearMomentum.assign(state[7], state[8], state[9]);
			rbdPtr->angularMomentum.assign(state[10], state[11], state[12]);
			rbdPtr->calculateDerivedParameters();
		}

		void OdeSolver::applyOde(const solid::core::Scalar timeStep, solid::core::RigidBody* rbdPtr)
		{
			state_type state;
			convertRigidBodyToStateArray(state, rbdPtr);
			Differential differential(rbdPtr);
			boost::numeric::odeint::integrate(differential, state, 0.0, timeStep, timeStep, observer);
			convertStateArrayToRigidBody(state, rbdPtr);
		}

		void OdeSolver::applyOdeWM(const solid::core::Scalar dt, solid::core::RigidBody* rbdPtr)
		{
//			std::cout << "------BEFORE------" << std::endl;
//			std::cout << "translation : " << rbdPtr->translation << std::endl;
//			std::cout << "rotationQuaternion : " << rbdPtr->rotationQuaternion << std::endl;
//			std::cout << "linearVelocity : " << rbdPtr->linearVelocity << std::endl;
//			std::cout << "angularVelocity : " << rbdPtr->angularVelocity << std::endl;
//			std::cout << "linearMomentum : " << rbdPtr->linearMomentum << std::endl;
//			std::cout << "angularMomentum : " << rbdPtr->angularMomentum << std::endl;
//			std::cout << "force : " << rbdPtr->force << std::endl;
//			std::cout << "torque : " << rbdPtr->torque << std::endl;

			// RK4 from Wild Magic
			Scalar halfDT = ((Scalar) 0.5) * dt;
			Scalar sixthDT = dt / ((Scalar) 6);

			Vector3d newPosition, newLinearMomentum, newAngularMomentum, newLinearVelocity,
					newAngularVelocity;
			Quaternion newQuatOrient;
			Matrix3d newRotOrient;

			// A1 = G(T,S0), B1 = S0 + (DT/2)*A1
			Vector3d A1DXDT = rbdPtr->linearVelocity;
			Quaternion W = Quaternion((Scalar) 0, rbdPtr->angularVelocity[0], rbdPtr->angularVelocity[1],
										rbdPtr->angularVelocity[2]);
			Quaternion A1DQDT = W * rbdPtr->rotationQuaternion * 0.5;
			Vector3d A1DPDT = rbdPtr->force;
			Vector3d A1DLDT = rbdPtr->torque;

			newPosition = rbdPtr->translation + halfDT * A1DXDT;
			newQuatOrient = rbdPtr->rotationQuaternion + A1DQDT * halfDT;
			newLinearMomentum = rbdPtr->linearMomentum + halfDT * A1DPDT;
			newAngularMomentum = rbdPtr->angularMomentum + halfDT * A1DLDT;
			newRotOrient = newQuatOrient.toRotationMatrix();
			newLinearVelocity = 1 / rbdPtr->mass * newLinearMomentum;
			newAngularVelocity = newRotOrient * rbdPtr->inertiaBodySpaceInverse * newRotOrient.transpose()
					* newAngularMomentum;

			// A2 = G(T+DT/2,B1), B2 = S0 + (DT/2)*A2
			Vector3d A2DXDT = newLinearVelocity;
			W = Quaternion((Scalar) 0, newAngularVelocity[0], newAngularVelocity[1], newAngularVelocity[2]);
			Quaternion A2DQDT = W * newQuatOrient * 0.5;
			Vector3d A2DPDT = rbdPtr->force;
			Vector3d A2DLDT = rbdPtr->torque;

			newPosition = rbdPtr->translation + halfDT * A2DXDT;
			newQuatOrient = rbdPtr->rotationQuaternion + A2DQDT * halfDT;
			newLinearMomentum = rbdPtr->linearMomentum + halfDT * A2DPDT;
			newAngularMomentum = rbdPtr->angularMomentum + halfDT * A2DLDT;
			newRotOrient = newQuatOrient.toRotationMatrix();
			newLinearVelocity = 1 / rbdPtr->mass * newLinearMomentum;
			newAngularVelocity = newRotOrient * rbdPtr->inertiaBodySpaceInverse * newRotOrient.transpose()
					* newAngularMomentum;

			// A3 = G(T+DT/2,B2), B3 = S0 + DT*A3
			Vector3d A3DXDT = newLinearVelocity;
			W = Quaternion((Scalar) 0, newAngularVelocity[0], newAngularVelocity[1], newAngularVelocity[2]);
			Quaternion A3DQDT = W * newQuatOrient * 0.5;
			Vector3d A3DPDT = rbdPtr->force;
			Vector3d A3DLDT = rbdPtr->torque;

			newPosition = rbdPtr->translation + dt * A3DXDT;
			newQuatOrient = rbdPtr->rotationQuaternion + A3DQDT * dt;
			newLinearMomentum = rbdPtr->linearMomentum + dt * A3DPDT;
			newAngularMomentum = rbdPtr->angularMomentum + dt * A3DLDT;
			newRotOrient = newQuatOrient.toRotationMatrix();
			newLinearVelocity = 1 / rbdPtr->mass * newLinearMomentum;
			newAngularVelocity = newRotOrient * rbdPtr->inertiaBodySpaceInverse * newRotOrient.transpose()
					* newAngularMomentum;

			// A4 = G(T+DT,B3), S1 = S0 + (DT/6)*(A1+2*(A2+A3)+A4)
			Vector3d A4DXDT = newLinearVelocity;
			W = Quaternion((Scalar) 0, newAngularVelocity[0], newAngularVelocity[1], newAngularVelocity[2]);
			Quaternion A4DQDT = W * newQuatOrient * 0.5;

			Vector3d A4DPDT = rbdPtr->force;
			Vector3d A4DLDT = rbdPtr->torque;

			rbdPtr->translation = rbdPtr->translation
					+ sixthDT * (A1DXDT + ((Scalar) 2) * (A2DXDT + A3DXDT) + A4DXDT);

			rbdPtr->rotationQuaternion = rbdPtr->rotationQuaternion
					+ (A1DQDT + (A2DQDT + A3DQDT) * ((Scalar) 2) + A4DQDT) * sixthDT;
			rbdPtr->rotationQuaternion.normalize();

			rbdPtr->linearMomentum = rbdPtr->linearMomentum
					+ sixthDT * (A1DPDT + ((Scalar) 2) * (A2DPDT + A3DPDT) + A4DPDT);

			rbdPtr->angularMomentum = rbdPtr->angularMomentum
					+ sixthDT * (A1DLDT + ((Scalar) 2) * (A2DLDT + A3DLDT) + A4DLDT);

			rbdPtr->calculateDerivedParameters();

//			std::cout << "------AFTER------" << std::endl;
//			std::cout << "mass : " << rbdPtr->mass << std::endl;
//			std::cout << "translation : " << rbdPtr->translation << std::endl;
//			std::cout << "rotationQuaternion : " << rbdPtr->rotationQuaternion << std::endl;
//			std::cout << "linearVelocity : " << rbdPtr->linearVelocity << std::endl;
//			std::cout << "angularVelocity : " << rbdPtr->angularVelocity << std::endl;
//			std::cout << "linearMomentum : " << rbdPtr->linearMomentum << std::endl;
//			std::cout << "angularMomentum : " << rbdPtr->angularMomentum << std::endl;
//			std::cout << "force : " << rbdPtr->force << std::endl;
//			std::cout << "torque : " << rbdPtr->torque << std::endl;

		}

	} /* namespace solver */
} /* namespace quarks */
