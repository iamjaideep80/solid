/*
 * AABB.cpp
 *
 *  Created on: 11-May-2014
 *      Author: jaideep
 */

#include "AABB.h"
#include <iostream>
#include <cmath>

namespace solid
{
	namespace core
	{

		AABB::AABB()
		{
		}

		AABB::AABB(Vector3 center, Vector3 halfWidth) :
				center(center), halfWidth(halfWidth)
		{
		}

		AABB::~AABB()
		{
		}

		const Vector3& AABB::getCenter() const
		{
			return center;
		}

		const Vector3& AABB::getHalfWidth() const
		{
			return halfWidth;
		}

		bool AABB::collisionDetect(const AABB& otherBBox)
		{
			Vector3 centerOther = otherBBox.getCenter();
			Vector3 halfWidthOther = otherBBox.getHalfWidth();
			for (int i = 0; i < 3; i++)
			{
				Scalar absDiff = std::abs((double) (center[i] - centerOther[i]));
				if (absDiff > (halfWidth[i] + halfWidthOther[i]))
					return false;
			}
			// We have an overlap
			return true;
		}

		void AABB::expandUsingPoint(Vector3 pointPos)
		{
			Vector3 minCorner = getMinCorner();
			Vector3 maxCorner = getMaxCorner();
			for (int i = 0; i < 3; i++)
			{
				if (minCorner[i] > pointPos[i])
					minCorner[i] = pointPos[i];
				if (maxCorner[i] < pointPos[i])
					maxCorner[i] = pointPos[i];
			}
			center = (minCorner + maxCorner) * 0.5;
			halfWidth = (maxCorner - minCorner) * 0.5;
		}

		Vector3 AABB::getMinCorner()
		{
			return Vector3(center[0] - halfWidth[0], center[1] - halfWidth[1], center[2] - halfWidth[2]);
		}

		Vector3 AABB::getMaxCorner()
		{
			return Vector3(center[0] + halfWidth[0], center[1] + halfWidth[1], center[2] + halfWidth[2]);
		}

		Vector3 AABB::getCorner(Bound boundX, Bound boundY, Bound boundZ)
		{
			Vector3 vec;
			vec[0] = center[0] + boundX * halfWidth[0];
			vec[1] = center[1] + boundY * halfWidth[1];
			vec[2] = center[2] + boundZ * halfWidth[2];
			return vec;
		}

	} /* namespace core */
} /* namespace solid */
