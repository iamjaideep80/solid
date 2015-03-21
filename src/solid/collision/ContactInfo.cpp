/*
 * CollisionInfo.cpp
 *
 *  Created on: 17-Nov-2014
 *      Author: jaideep
 */

#include "ContactInfo.h"

namespace solid
{
	namespace collision
	{
		using namespace solid::core;
		ContactInfo::ContactInfo(solid::core::RigidBody* bodyAPtr, solid::core::RigidBody* bodyBPtr,
				CollisionPointInfo collPointInfo) :
				bodyAPtr(bodyAPtr), bodyBPtr(bodyBPtr), collPointInfo(collPointInfo)
		{
			calculateRelativeVelocity();
		}

		ContactInfo::~ContactInfo()
		{
		}

		solid::core::Scalar ContactInfo::getRelativeVelocity()
		{
			calculateRelativeVelocity();
			return vRel;
		}

		void ContactInfo::calculateRelativeVelocity()
		{
			Vector3 pointPos = collPointInfo.pointPos;
			Vector3 pADot = bodyAPtr->ptVelocity(pointPos);
			Vector3 pBDot = bodyBPtr->ptVelocity(pointPos);
			Vector3 normal = collPointInfo.direction;
			normal.normalize();
			vRel = normal.dot(pADot - pBDot);
		}

		ContactType ContactInfo::getContactType()
		{
			Scalar thresholdVel = 0.1;
			Scalar vrel = getRelativeVelocity();
			ContactType type;
			if (vrel > thresholdVel)
			{
				type = SEPARATING_CONTACT;
			}
			if (vrel <= thresholdVel && vrel >= -thresholdVel)
			{
				type = RESTING_CONTACT;
			}
			if (vrel < -thresholdVel)
			{
				type = COLLIDING_CONTACT;
			}
			return type;
		}

	} /* namespace collision */
} /* namespace solid */
