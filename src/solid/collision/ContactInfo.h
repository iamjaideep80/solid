/*
 * CollisionInfo.h
 *
 *  Created on: 17-Nov-2014
 *      Author: jaideep
 */

#ifndef COLLISIONINFO_H_
#define COLLISIONINFO_H_

#include "solid/core/CommonTypes.h"
#include "solid/core/RigidBody.h"
#include "CollisionPointInfo.h"
#include "ContactType.h"

namespace solid
{
	namespace collision
	{
		class ContactInfo
		{
		public:
			ContactInfo(solid::core::RigidBody* bodyAPtr, solid::core::RigidBody* bodyBPtr,
					CollisionPointInfo collPointInfo);
			virtual ~ContactInfo();
		public:
			CollisionPointInfo collPointInfo;
			solid::core::RigidBody* bodyAPtr;
			solid::core::RigidBody* bodyBPtr;
			solid::core::Scalar vRel;
			void calculateRelativeVelocity();
			solid::core::Scalar getRelativeVelocity();
			ContactType getContactType();
		};

	} /* namespace collision */
} /* namespace solid */
#endif /* COLLISIONINFO_H_ */
