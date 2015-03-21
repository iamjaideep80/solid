/*
 * SimData.h
 *
 *  Created on: 30-Apr-2014
 *      Author: jaideep
 */

#ifndef SIMDATA_H_
#define SIMDATA_H_

#include <vector>
//#include "RigidBody.h"
#include "CommonTypes.h"

namespace solid
{
	namespace core
	{
		class RigidBody;
		class SimData
		{
		public:
			SimData();
			SimData(const SimData & other);
			void operator=(const SimData & other);
			SimData(Scalar resetFrame, Scalar subSteps, Scalar maxSubSteps,Scalar simulationTimeScale,Scalar collisionTolerance);
			virtual ~SimData();

			Scalar getResetFrame() const
			{
				return resetFrame;
			}

			Scalar getSimulationTimeScale() const
			{
				return simulationTimeScale;
			}

			Scalar getSubSteps() const
			{
				return subSteps;
			}

			Scalar getMaxSubSteps() const
			{
				return maxSubSteps;
			}

			void setMaxSubSteps(Scalar maxSubSteps)
			{
				this->maxSubSteps = maxSubSteps;
			}

			Scalar getCollisionTolerance() const
			{
				return collisionTolerance;
			}

			void setCollisionTolerance(Scalar collisionTolerance)
			{
				this->collisionTolerance = collisionTolerance;
			}

			std::vector<RigidBody*> rigidBodyVector;
		private:
			Scalar resetFrame;
			Scalar subSteps;
			Scalar maxSubSteps;
			Scalar simulationTimeScale;
			Scalar collisionTolerance;
		};

	} /* namespace core */
} /* namespace solid */
#endif /* SIMDATA_H_ */
