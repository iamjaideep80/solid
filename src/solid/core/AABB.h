/*
 * AABB.h
 *
 *  Created on: 11-May-2014
 *      Author: jaideep
 */

#ifndef AABB_H_
#define AABB_H_

#include "CommonTypes.h"

namespace solid
{
	namespace core
	{
		enum Bound
		{
			MIN = -1, MAX = +1
		};
		class AABB
		{
		public:
			AABB();
			AABB(Vector3 center, Vector3 halfWidth);
			virtual ~AABB();
			const Vector3& getCenter() const;
			const Vector3& getHalfWidth() const;
			bool collisionDetect(const AABB& otherBBox);
			void expandUsingPoint(Vector3 pointPos);
			Vector3 getMinCorner();
			Vector3 getMaxCorner();
			Vector3 getCorner(Bound boundX, Bound boundY, Bound boundZ);
		private:
			Vector3 center;
			Vector3 halfWidth;
		};

	} /* namespace core */
} /* namespace solid */
#endif /* AABB_H_ */
