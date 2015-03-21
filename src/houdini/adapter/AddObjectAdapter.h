/*
 * AddObjectAdapter.h
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#ifndef ADDOBJECTADAPTER_H_
#define ADDOBJECTADAPTER_H_

#include "solid/core/SimData.h"

#include "GU/GU_Detail.h"
#include "GU/GU_PrimPolySoup.h"
#include "solid/core/InitialState.h"

namespace solid
{
	namespace houdini
	{
		namespace adapter
		{

			class AddObjectAdapter
			{
			public:
				AddObjectAdapter(solid::core::SimData* simDataPtr, const GU_Detail* sourceObjGdp);
				virtual ~AddObjectAdapter();
				void addObjectsToSim();
			private:
				solid::core::InitialState extractInitialState(const GEO_Primitive* primPtr);
				solid::core::SimData* simDataPtr;
				const GU_Detail* sourceObjGdp;
			};

		} /* namespace adapter */
	} /* namespace houdini */
} /* namespace solid */
#endif /* ADDOBJECTADAPTER_H_ */
