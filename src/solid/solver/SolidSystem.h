/*
 * SolidSystem.h
 *
 *  Created on: 01-May-2014
 *      Author: jaideep
 */

#ifndef SOLIDSYSTEM_H_
#define SOLIDSYSTEM_H_

#include "solid/core/CommonTypes.h"
#include "solid/core/SimData.h"
#include "solid/collision/CollisionState.h"
#include "solid/collision/CollisionManager.h"

namespace solid
{
	namespace solver
	{
		class SolidSystem
		{
		public:
			SolidSystem(solid::core::SimData* simDataPtr);
			virtual ~SolidSystem();
			void stepForward(solid::core::Scalar timeStep);

		private:
			solid::core::SimData* simDataPtr;
			solid::core::SimData* backupSimDataPtr;
			solid::core::Scalar numOfSteps;
			solid::core::Scalar maxNumOfSteps;
			solid::core::Scalar x;
			solid::core::Scalar y;
			solid::core::Scalar z;
			solid::core::Scalar completedTime;
			solid::core::Scalar currentTime;
			solid::collision::CollisionManager collManager;
			void internalStepForward(solid::core::Scalar timeStep);
			void stepBackward();
			void syncBackup();
			void respondToContacts();
			void deepIntersectionResponse();
			void completeRemainingTimeStep();
			void applyOdeToAllObjects(solid::core::Scalar timeStep);
		};

	} /* namespace solver */
} /* namespace solid */
#endif /* SOLIDSYSTEM_H_ */
