/*
 * SimData.cpp
 *
 *  Created on: 30-Apr-2014
 *      Author: jaideep
 */

#include "SimData.h"
#include "solid/core/RigidBody.h"
namespace solid
{
	namespace core
	{

		SimData::SimData(Scalar resetFrame, Scalar subSteps, Scalar maxSubSteps, Scalar simulationTimeScale,
				Scalar collisionTolerance) :
				resetFrame(resetFrame), subSteps(subSteps), maxSubSteps(maxSubSteps),
						simulationTimeScale(simulationTimeScale), collisionTolerance(collisionTolerance)
		{
		}

		SimData::SimData()
		{
			resetFrame = 0;
			subSteps = 1;
			maxSubSteps = 1;
			simulationTimeScale = 1;
			collisionTolerance = 0.01;
		}

		SimData::SimData(const SimData & other)
		{
			resetFrame = other.resetFrame;
			subSteps = other.subSteps;
			maxSubSteps = other.maxSubSteps;
			simulationTimeScale = other.simulationTimeScale;
			collisionTolerance = other.collisionTolerance;
			rigidBodyVector = other.rigidBodyVector;
			for (int i = 0; i < rigidBodyVector.size(); i++)
			{
				rigidBodyVector[i] = new RigidBody(*other.rigidBodyVector[i]);
			}
//			*this = other;
		}

		void SimData::operator =(const SimData& other)
		{
			resetFrame = other.resetFrame;
			subSteps = other.subSteps;
			maxSubSteps = other.maxSubSteps;
			simulationTimeScale = other.simulationTimeScale;
			collisionTolerance = other.collisionTolerance;
//			rigidBodyVector = other.rigidBodyVector;
			for (int i = 0; i < rigidBodyVector.size(); i++)
			{
				*rigidBodyVector[i] = *other.rigidBodyVector[i];
			}

		}

		SimData::~SimData()
		{
			for (int i = 0; i < rigidBodyVector.size(); i++)
			{
				delete rigidBodyVector[i];
			}
			rigidBodyVector.clear();
		}

	} /* namespace core */
} /* namespace solid */
