/*
 * SolveSimAdapter.h
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#ifndef SOLVESIMADAPTER_H_
#define SOLVESIMADAPTER_H_

#include "solid/solver/SolidSystem.h"
#include "solid/core/SimData.h"

namespace solid
{
	namespace houdini
	{
		namespace adapter
		{
			class SolveSimAdapter
			{
			public:
				SolveSimAdapter(solid::core::SimData* simDataPtr);
				virtual ~SolveSimAdapter();
				void stepForward(double fps, int subSteps);
			private:
				solid::solver::SolidSystem solidSystem;
			};
		} /* namespace adapter */
	} /* namespace houdini */
} /* namespace solid */
#endif /* SOLVESIMADAPTER_H_ */
