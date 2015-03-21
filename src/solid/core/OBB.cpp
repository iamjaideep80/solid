/*
 * OBB.cpp
 *
 *  Created on: 18-May-2014
 *      Author: jaideep
 */

#include "OBB.h"

namespace solid
{
	namespace core
	{

		OBB::OBB()
		{
		}

		OBB::OBB(Vector3 center, Vector3 halfWidth, Vector3* axisArray) :
				c(center), e(halfWidth)
		{
			u[0] = axisArray[0];
			u[1] = axisArray[1];
			u[2] = axisArray[2];
		}

		OBB::~OBB()
		{
		}

	} /* namespace core */
} /* namespace solid */
