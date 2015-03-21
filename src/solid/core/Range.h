/*
 * Range.h
 *
 *  Created on: 01-Jun-2014
 *      Author: jaideep
 */

#ifndef RANGE_H_
#define RANGE_H_

#include "CommonTypes.h"
#include "solid/collision/CollisionPointInfo.h"

namespace solid
{
	namespace core
	{

		class Range
		{
		public:
			Range(Vector3 dir, Vector3 pointPos);
			virtual ~Range();
			void addToRange(Vector3 pointPos);
			bool testRangeCollision(Range other, solid::collision::CollisionPointInfo & info);
		private:
			Scalar min;
			Vector3 minPointPos;
			Scalar max;
			Vector3 maxPointPos;
			Vector3 dir;
		};

	} /* namespace core */
} /* namespace solid */
#endif /* RANGE_H_ */
