/*
 * RestingContactResponse.cpp
 *
 *  Created on: 01-Dec-2014
 *      Author: jaideep
 */

#include "RestingContactResponse.h"
#include "solid/core/RigidBody.h"

namespace solid
{
	namespace collision
	{
		using namespace solid::core;
		RestingContactResponse::RestingContactResponse(
				std::vector<solid::collision::ContactInfo> restingContactList) :
				restingContactList(restingContactList)
		{
			numOfContacts = restingContactList.size();

			matrixA.resize(numOfContacts);
			for (int i = 0; i < numOfContacts; i++)
				matrixA[i].resize(numOfContacts);

		}

		RestingContactResponse::~RestingContactResponse()
		{
		}

		void RestingContactResponse::computeMatrixA()
		{
			for (int i = 0; i < numOfContacts; i++)
				for (int j = 0; j < numOfContacts; j++)
					matrixA[i][j] = computeAij(restingContactList[i], restingContactList[j]);
		}

		solid::core::Scalar RestingContactResponse::computeAij(solid::collision::ContactInfo ci,
				solid::collision::ContactInfo cj)
		{
			if ((ci.bodyAPtr != cj.bodyAPtr) && (ci.bodyBPtr != cj.bodyBPtr) && (ci.bodyAPtr != cj.bodyBPtr)
					&& (ci.bodyBPtr != cj.bodyAPtr))
				return 0.0;

			RigidBody* A = ci.bodyAPtr;
			RigidBody* B = ci.bodyBPtr;
			Vector3 ni = ci.collPointInfo.direction;
			Vector3 nj = cj.collPointInfo.direction;
			Vector3 pi = ci.collPointInfo.pointPos;
			Vector3 pj = cj.collPointInfo.pointPos;
			Vector3 ra = Vector3(pi - A->translation);
			Vector3 rb = Vector3(pi - B->translation);

			// Force On Body A
			Vector3 force_on_a(0, 0, 0);
			Vector3 torque_on_a(0, 0, 0);

			if (cj.bodyAPtr == ci.bodyAPtr)
			{
				force_on_a = nj;
				torque_on_a = (pj - A->translation).cross(nj);
			}
			else if (cj.bodyBPtr == ci.bodyAPtr)
			{
				force_on_a = -1 * nj;
				torque_on_a = (pj - A->translation).cross(nj);
			}

			// Force On Body B
			Vector3 force_on_b(0, 0, 0);
			Vector3 torque_on_b(0, 0, 0);

			if (cj.bodyAPtr == ci.bodyBPtr)
			{
				force_on_b = nj;
				torque_on_b = (pj - B->translation).cross(nj);
			}
			else if (cj.bodyBPtr == ci.bodyBPtr)
			{
				force_on_b = -1 * nj;
				torque_on_b = (pj - B->translation).cross(nj);
			}

			// Compute a_linear a_angular
			Vector3 a_linear = Vector3(force_on_a / A->mass);
			Vector3 a_angularTmp = Vector3(A->inertiaInverse * torque_on_a);
			Vector3 a_angular = a_angularTmp.cross(ra);

			// Compute b_linear b_angular
			Vector3 b_linear = Vector3(force_on_b / B->mass);
			Vector3 b_angularTmp = Vector3(B->inertiaInverse * torque_on_b);
			Vector3 b_angular = b_angularTmp.cross(rb);

			Vector3 tmp = Vector3((a_linear + a_angular) - (b_linear + b_angular));
			return ni.dot(tmp);
			return 0.0;
		}

		void RestingContactResponse::computeVectorB()
		{
			for (int i = 0; i < numOfContacts; i++)
			{
				solid::collision::ContactInfo* c = &restingContactList[i];
				RigidBody* A = c->bodyAPtr;
				RigidBody* B = c->bodyBPtr;
				Vector3 n = c->collPointInfo.direction;
				Vector3 ra = Vector3(c->collPointInfo.pointPos - A->translation);
				Vector3 rb = Vector3(c->collPointInfo.pointPos - B->translation);

				Vector3 f_ext_a = A->force;
				Vector3 f_ext_b = B->force;
				Vector3 t_ext_a = A->torque;
				Vector3 t_ext_b = B->torque;

				Vector3 a_ext_part = Vector3((f_ext_a / A->mass) + ((A->inertiaInverse * t_ext_a).cross(ra)));
				Vector3 b_ext_part = Vector3((f_ext_b / B->mass) + ((B->inertiaInverse * t_ext_b).cross(rb)));

				Vector3 a_vel_part_1 = A->angularVelocity.cross(A->angularVelocity.cross(ra));
				Vector3 a_vel_part_2 = Vector3(
						A->inertiaInverse * (A->angularMomentum.cross(A->angularVelocity)));
				Vector3 a_vel_part_3 = a_vel_part_2.cross(ra);
				Vector3 a_vel_part = Vector3(a_vel_part_1 + a_vel_part_3);

				Vector3 b_vel_part_1 = B->angularVelocity.cross(B->angularVelocity.cross(rb));
				Vector3 b_vel_part_2 = Vector3(
						B->inertiaInverse * (B->angularMomentum.cross(B->angularVelocity)));
				Vector3 b_vel_part_3 = b_vel_part_2.cross(rb);
				Vector3 b_vel_part = Vector3(b_vel_part_1 + b_vel_part_3);

				Vector3 k1_part = Vector3((a_ext_part + a_vel_part) - (b_ext_part + b_vel_part));
				Scalar k1 = n.dot(k1_part);
				// TO BE COMPLETED

			}
		}

	} /* namespace collision */
} /* namespace solid */
