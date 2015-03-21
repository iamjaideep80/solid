/*
 * SolidSystem.cpp
 *
 *  Created on: 01-May-2014
 *      Author: jaideep
 */

#include "SolidSystem.h"
#include "State.h"
#include "OdeSolver.h"

namespace solid
{
	namespace solver
	{
		using namespace solid::core;
		using namespace solid::collision;

		SolidSystem::SolidSystem(SimData* simDataPtr) :
				simDataPtr(simDataPtr)
		{
			backupSimDataPtr = new SimData(*simDataPtr);
			syncBackup();
			numOfSteps = 0;
			maxNumOfSteps = simDataPtr->getMaxSubSteps();
			completedTime = 0;
			collManager.initialize(simDataPtr);
		}

		SolidSystem::~SolidSystem()
		{
//			delete backupSimDataPtr;
		}

		void SolidSystem::stepForward(Scalar fullTimeStep)
		{
			x = 0;
			y = 0;
			z = fullTimeStep;
			internalStepForward(fullTimeStep);
			completedTime = completedTime + z;
		}

		void SolidSystem::internalStepForward(solid::core::Scalar curTimeStep)
		{
			numOfSteps++;
			if (numOfSteps > maxNumOfSteps)
			{
				std::cout << "MAX SUBSTEPS REACHED" << std::endl;
				return;
			}

			y = x + curTimeStep;

			applyOdeToAllObjects(curTimeStep);

//			CollisionState combinedCollState = findAllCollisions();
			CollisionState combinedCollState = collManager.findAllCollisions();

			switch (combinedCollState)
			{
			case NO_CONTACT:
				//std::cout << "No Contact" << std::endl;
				completeRemainingTimeStep();
				break;
			case CONTACT:
//				std::cout << "Contact" << std::endl;
				respondToContacts();
				break;
			case DEEP_INTERSECTION:
//				std::cout << "Deep Intersection" << std::endl;
				deepIntersectionResponse();
				break;
			}
		}
		void SolidSystem::applyOdeToAllObjects(solid::core::Scalar timeStep)
		{
			for (int i = 0; i < simDataPtr->rigidBodyVector.size(); i++)
			{
				RigidBody* rigidBodyPtr = simDataPtr->rigidBodyVector[i];
				rigidBodyPtr->collided = false;
//				if (rigidBodyPtr->active)
//				{
				OdeSolver solver;
//					solver.applyOde(timeStep, rigidBodyPtr);
				solver.applyOdeWM(timeStep, rigidBodyPtr);
//				}
			}
		}

		void SolidSystem::completeRemainingTimeStep()
		{
			syncBackup();
			Scalar remainingTimeStep = z - x;
			if (remainingTimeStep > 0)
				internalStepForward(remainingTimeStep);
		}

		void SolidSystem::respondToContacts()
		{
			collManager.respondToContacts();
			completeRemainingTimeStep();
		}

		void SolidSystem::deepIntersectionResponse()
		{
			Scalar halfTimeStep = (y - x) / 2;
			stepBackward();
			internalStepForward(halfTimeStep);
		}

		void SolidSystem::stepBackward()
		{
			*simDataPtr = *backupSimDataPtr;
			y = x;
		}

		void SolidSystem::syncBackup()
		{
			*backupSimDataPtr = *simDataPtr;
			x = y;
		}

	} /* namespace solver */
} /* namespace solid */
