/*
 * CollisionPointInfo.cpp
 *
 *  Created on: 02-Jun-2014
 *      Author: jaideep
 */

#include "CollisionPointInfo.h"

namespace solid
{
	namespace collision
	{
		using namespace solid::core;
		CollisionPointInfo::CollisionPointInfo()
		{
			intersectionDist = 0;
			pointPos = Vector3(0, 0, 0);
			direction = Vector3(0, 0, 0);

		}

		CollisionPointInfo::~CollisionPointInfo()
		{
		}

	} /* namespace collision */
} /* namespace solid */
