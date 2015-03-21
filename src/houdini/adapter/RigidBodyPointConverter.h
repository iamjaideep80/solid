/*
 * RigidBodyPointConverter.h
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#ifndef RIGIDBODYPOINTCONVERTER_H_
#define RIGIDBODYPOINTCONVERTER_H_

#include "solid/core/RigidBody.h"
#include "GU/GU_Detail.h"
#include "GEO/GEO_Point.h"

namespace solid
{
	namespace houdini
	{
		namespace adapter
		{

			class RigidBodyPointConverter
			{
			public:
				RigidBodyPointConverter();
				virtual ~RigidBodyPointConverter();
				void convertRigidBodyToPoint(solid::core::RigidBody* rigidBodyPtr, GU_Detail* gdp,
						GEO_Point* pointPtr);
			};

		} /* namespace converter */
	} /* namespace houdini */
} /* namespace solid */
#endif /* RIGIDBODYPOINTCONVERTER_H_ */
