/*
 * Range.cpp
 *
 *  Created on: 01-Jun-2014
 *      Author: jaideep
 */

#include "Range.h"

namespace solid
{
	namespace core
	{

		Range::Range(Vector3 dir, Vector3 pointPos) :
				dir(dir)
		{
			Scalar projection = dir.dot(pointPos);
			min = projection;
			minPointPos = pointPos;
			max = projection;
			maxPointPos = pointPos;
		}

		Range::~Range()
		{
		}

		void Range::addToRange(Vector3 pointPos)
		{
			Scalar projection = dir.dot(pointPos);
			if (projection < min)
			{
				min = projection;
				minPointPos = pointPos;
			}
			if (projection > max)
			{
				max = projection;
				maxPointPos = pointPos;
			}
		}

		bool Range::testRangeCollision(Range other, solid::collision::CollisionPointInfo & info)
		{
			if ((this->min < other.min) && (this->max > other.min))
			{
				info.intersectionDist = this->max - other.min;
				info.direction = dir;
				info.pointPos = (this->maxPointPos + other.minPointPos) / 2;
				return true;
			}
			if ((this->min > other.min) && (other.max > this->min))
			{
				info.intersectionDist = other.max - this->min;
				info.direction = dir;
				info.pointPos = (this->minPointPos + other.maxPointPos) / 2;
				return true;
			}
			return false;
		}

	} /* namespace core */
} /* namespace solid */
