/*
 * CollidingContactResponse.cpp
 *
 *  Created on: 18-Jul-2014
 *      Author: jaideep
 */

#include "CollidingContactResponse.h"

namespace solid
{
	namespace collision
	{
		using namespace solid::core;
		CollidingContactResponse::CollidingContactResponse(ContactInfo contactInfo) :
				contactInfo(contactInfo)
		{
		}

		CollidingContactResponse::~CollidingContactResponse()
		{
		}

		void CollidingContactResponse::modifyPosition()
		{
			solid::core::RigidBody* bodyAPtr = contactInfo.bodyAPtr;
			solid::core::RigidBody* bodyBPtr = contactInfo.bodyBPtr;
			CollisionPointInfo info = contactInfo.collPointInfo;

			Scalar totalMass = bodyAPtr->mass + bodyBPtr->mass;
			Scalar contributionA = bodyBPtr->mass / totalMass;
			Scalar contributionB = bodyAPtr->mass / totalMass;
			bodyAPtr->translation += contributionA * info.intersectionDist * info.direction;
			bodyBPtr->translation -= contributionB * info.intersectionDist * info.direction;
		}

		void CollidingContactResponse::modifyVelocity()
		{
			solid::core::RigidBody* bodyAPtr = contactInfo.bodyAPtr;
			solid::core::RigidBody* bodyBPtr = contactInfo.bodyBPtr;
			CollisionPointInfo info = contactInfo.collPointInfo;

			Vector3 pointPos = info.pointPos;
			Vector3 normal = info.direction;
			normal.normalize();
			Scalar vrel = contactInfo.getRelativeVelocity();

			Vector3 rA = Vector3(pointPos - bodyAPtr->translation);
			Vector3 rB = Vector3(pointPos - bodyBPtr->translation);


			Scalar epsilon = bodyAPtr->bounce * bodyBPtr->bounce;

			Scalar numerator = -(1 + epsilon) * vrel;
//			// Resting contact code
//			Scalar velFromAccel = (bodyAPtr->force / bodyAPtr->mass).dot(info.direction);
//			std::cout << "velFromAccel " << velFromAccel << std::endl;
//			Scalar numerator = -vrel - epsilon * vrel + epsilon * velFromAccel;
//			// Resting contact code

			Scalar term1 = 1 / bodyAPtr->mass;
			Scalar term2 = 1 / bodyBPtr->mass;

			Vector3 rAN = rA.cross(normal);
			Vector3 IinvrAN = Vector3(bodyAPtr->inertiaInverse * rAN);
			Vector3 IinvrANCrossRA = IinvrAN.cross(rA);
			Vector3 rBN = rB.cross(normal);
			Vector3 IinvrBN = Vector3(bodyBPtr->inertiaInverse * rBN);
			Vector3 IinvrBNCrossRB = IinvrBN.cross(rB);

			Scalar term3 = normal.dot(IinvrANCrossRA);
			Scalar term4 = normal.dot(IinvrBNCrossRB);

			Scalar j = numerator / (term1 + term2 + term3 + term4);
			Vector3 impulse = Vector3(j * normal);

			bodyAPtr->linearMomentum += impulse;
			bodyBPtr->linearMomentum -= impulse;
			bodyAPtr->angularMomentum += rA.cross(impulse);
			bodyBPtr->angularMomentum -= rB.cross(impulse);

			bodyAPtr->calculateDerivedParameters();
			bodyBPtr->calculateDerivedParameters();
		}

	} /* namespace collision */
} /* namespace solid */
