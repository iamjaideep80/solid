/*
 * CollisionPointInfo.h
 *
 *  Created on: 02-Jun-2014
 *      Author: jaideep
 */

#ifndef COLLISIONPOINTINFO_H_
#define COLLISIONPOINTINFO_H_

#include "solid/core/CommonTypes.h"

namespace solid
{
	namespace collision
	{

		class CollisionPointInfo
		{
		public:
			CollisionPointInfo();
			virtual ~CollisionPointInfo();
		public:
			solid::core::Scalar intersectionDist;
			solid::core::Vector3 pointPos;
			solid::core::Vector3 direction;
		};

	} /* namespace collision */
} /* namespace solid */
#endif /* COLLISIONPOINTINFO_H_ */
