/*
 * SolveSimAdapter.cpp
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#include "SolveSimAdapter.h"

namespace solid
{
	namespace houdini
	{
		namespace adapter
		{

			SolveSimAdapter::SolveSimAdapter(solid::core::SimData* simDataPtr) :
					solidSystem(simDataPtr)
			{
			}

			SolveSimAdapter::~SolveSimAdapter()
			{
			}

			void SolveSimAdapter::stepForward(double fps, int subSteps)
			{
				for (int i = 0; i < subSteps; i++)
				{
					solidSystem.stepForward(1 / (fps * float(subSteps)));
				}
			}

		} /* namespace adapter */
	} /* namespace houdini */
} /* namespace solid */
