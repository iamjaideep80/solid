/*
 * BlindDataManager.h
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#ifndef BLINDDATAMANAGER_H_
#define BLINDDATAMANAGER_H_

#include "GU/GU_Detail.h"
#include "solid/core/SimData.h"

namespace solid
{
	namespace houdini
	{
		class BlindDataManager
		{
		public:
			BlindDataManager();
			virtual ~BlindDataManager();
			core::SimData* extractSimDataPtr(GU_Detail* gdp);
			void insertSimDataPtr(GU_Detail* gdp, solid::core::SimData* simDataPtr);
		};

	} /* namespace houdini */
} /* namespace solid */
#endif /* BLINDDATAMANAGER_H_ */
