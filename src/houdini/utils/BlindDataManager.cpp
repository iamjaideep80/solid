/*
 * BlindDataManager.cpp
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#include "BlindDataManager.h"

#include "GA/GA_AIFBlindData.h"

namespace solid
{
	namespace houdini
	{

		BlindDataManager::BlindDataManager()
		{
		}

		BlindDataManager::~BlindDataManager()
		{
		}

		core::SimData* BlindDataManager::extractSimDataPtr(GU_Detail* gdp)
		{
			const GA_ROAttributeRef attrRef = gdp->findAttribute(GA_ATTRIB_DETAIL, GA_SCOPE_PUBLIC,
																	"SimData");
			const GA_Attribute *attr = attrRef.getAttribute();
			const GA_AIFBlindData *blindData = attr->getAIFBlindData();
			return blindData->getValue<solid::core::SimData*>(attr, 0);
		}

		void BlindDataManager::insertSimDataPtr(GU_Detail* gdp, solid::core::SimData* simDataPtr)
		{
			GA_RWAttributeRef attrRef = gdp->createAttribute(GA_ATTRIB_DETAIL, GA_SCOPE_PUBLIC, "SimData",
																NULL, NULL, "blinddata");
			GA_Attribute *attr = attrRef.getAttribute();
			const GA_AIFBlindData* blindData = attr->getAIFBlindData();
			blindData->setDataSize(attr, sizeof(solid::core::SimData*), &simDataPtr);
		}

	} /* namespace houdini */
} /* namespace solid */
