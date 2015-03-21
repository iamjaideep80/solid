/*
 * CollisionDetectorSAT.h
 *
 *  Created on: 18-May-2014
 *      Author: jaideep
 */

#ifndef COLLISIONDETECTORSAT_H_
#define COLLISIONDETECTORSAT_H_

#include "solid/core/OBB.h"

namespace solid
{
	namespace collision
	{

		class ObbCollisionDetector
		{
		public:
			ObbCollisionDetector();
			virtual ~ObbCollisionDetector();
			bool TestCollision(solid::core::OBB& a, solid::core::OBB& b);
		};

	} /* namespace collision */
} /* namespace solid */
#endif /* COLLISIONDETECTORSAT_H_ */
