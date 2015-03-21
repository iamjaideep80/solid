/*
 * CollisionManager.cpp
 *
 *  Created on: 17-Nov-2014
 *      Author: jaideep
 */

#include "CollisionManager.h"
#include "solid/collision/ObbCollisionDetector.h"
#include "solid/collision/PolyhedronCollisionDetector.h"
#include "solid/collision/CollidingContactResponse.h"
#include "solid/collision/RestingContactResponse.h"
#include "solid/core/CommonTypes.h"

namespace solid
{
	namespace collision
	{
		using namespace solid::core;
		CollisionManager::CollisionManager()
		{
			simDataPtr = NULL;
			contactList.clear();
		}

		CollisionManager::~CollisionManager()
		{
		}

		void CollisionManager::initialize(solid::core::SimData* simDataPtr)
		{
			this->simDataPtr = simDataPtr;
			contactList.clear();
		}

		solid::collision::CollisionState CollisionManager::findAllCollisions()
		{
			CollisionState combinedCollState = NO_CONTACT;
			for (int i = 0; i < simDataPtr->rigidBodyVector.size() - 1; i++)
			{
				for (int j = i + 1; j < simDataPtr->rigidBodyVector.size(); j++)
				{
					RigidBody* bodyAPtr = simDataPtr->rigidBodyVector[i];
					RigidBody* bodyBPtr = simDataPtr->rigidBodyVector[j];
					CollisionState collState = twoPhaseCollisionDetection(bodyAPtr, bodyBPtr);
					if (collState == DEEP_INTERSECTION)
						combinedCollState = DEEP_INTERSECTION;
					if (collState == CONTACT && combinedCollState == NO_CONTACT)
						combinedCollState = CONTACT;
				}
			}
			return combinedCollState;
		}

		solid::collision::CollisionState CollisionManager::twoPhaseCollisionDetection(RigidBody* bodyAPtr,
				RigidBody* bodyBPtr)
		{
			ObbCollisionDetector obbCollisionDetector;
			bool broadPhaseCollision = obbCollisionDetector.TestCollision(bodyAPtr->obbWorldSpace,
																			bodyBPtr->obbWorldSpace);
			if (broadPhaseCollision)
			{
				PolyhedronCollisionDetector polyhedronCollisionDetector(bodyAPtr->geomWorldSpacePtr,
																		bodyBPtr->geomWorldSpacePtr);
				CollisionPointInfo info;
				bool narrowPhaseCollision = polyhedronCollisionDetector.TestCollision(info);
				if (narrowPhaseCollision)
				{
					if (info.intersectionDist < simDataPtr->getCollisionTolerance())
					{
						ContactInfo contactInfo(bodyAPtr, bodyBPtr, info);
						if (contactInfo.getContactType() != SEPARATING_CONTACT)
						{
							contactList.push_back(contactInfo);
						}
//						CollisionResponse response(bodyAPtr, bodyBPtr, info);
						bodyAPtr->collided = true;
						bodyBPtr->collided = true;
						return CONTACT;
					}
					else
					{
						return DEEP_INTERSECTION;
					}
				}
			}
			return NO_CONTACT;
		}

		void CollisionManager::respondToContacts()
		{
			resolveCollidingContacts();
			resolveRestingContacts();
			contactList.clear();
		}

		void CollisionManager::resolveCollidingContacts()
		{
			//Resolve Colliding contacts
			for (int i = 0; i < contactList.size(); i++)
			{
				if (contactList[i].getContactType() == SEPARATING_CONTACT)
					continue;

				CollidingContactResponse collidingContactResponse(contactList[i]);
				collidingContactResponse.modifyPosition();
				collidingContactResponse.modifyVelocity();
			}
		}

		void CollisionManager::resolveRestingContacts()
		{
			//Resolve Resting Contacts
			filterRestingContacts();
			RestingContactResponse restingContactResponse(restingContactList);
		}

void CollisionManager::filterRestingContacts()
		{
			//Resolve Resting Contacts
			restingContactList.clear();
			for (int i = 0; i < contactList.size(); i++)
			{
				ContactType type = contactList[i].getContactType();
				switch (type)
				{
				case SEPARATING_CONTACT:
				{
					//					std::cout << "Separating Contact" << std::endl;
					break;
				}
				case COLLIDING_CONTACT:
				{
					std::cout << "Colliding Contact" << std::endl;
					break;
				}
				case RESTING_CONTACT:
				{
					std::cout << "Resting Contact" << std::endl;
					restingContactList.push_back(contactList[i]);
					break;
				}
				}
			}
		}

			} /* namespace collision */
} /* namespace solid */
