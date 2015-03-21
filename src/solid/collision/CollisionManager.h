/*
 * CollisionManager.h
 *
 *  Created on: 17-Nov-2014
 *      Author: jaideep
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

#include "solid/core/SimData.h"
#include "CollisionState.h"
#include "ContactType.h"
#include "ContactInfo.h"

namespace solid
{
	namespace collision
	{
		using solid::core::RigidBody;
		using namespace solid::collision;
		class CollisionManager
		{
		public:
			CollisionManager();
			virtual ~CollisionManager();
			void initialize(solid::core::SimData* simDataPtr);
			solid::collision::CollisionState findAllCollisions();
			void respondToContacts();
		private:
			solid::collision::CollisionState twoPhaseCollisionDetection(solid::core::RigidBody* bodyAPtr,
					solid::core::RigidBody* bodyBPtr);
			solid::core::SimData* simDataPtr;
			std::vector<solid::collision::ContactInfo> contactList;
			std::vector<solid::collision::ContactInfo> restingContactList;
			void resolveCollidingContacts();
			void resolveRestingContacts();
			void filterRestingContacts();
		};

	} /* namespace collision */
} /* namespace solid */
#endif /* COLLISIONMANAGER_H_ */
