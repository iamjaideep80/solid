/*
 * OBB.h
 *
 *  Created on: 18-May-2014
 *      Author: jaideep
 */

#ifndef OBB_H_
#define OBB_H_
#include "CommonTypes.h"

namespace solid
{
	namespace core
	{

		class OBB
		{
		public:
			OBB();
			OBB(Vector3 center, Vector3 halfWidth, Vector3* axisArray);
			virtual ~OBB();
		public:
			Vector3 c;
			Vector3 e;
			Vector3 u[3];
		};

	} /* namespace core */
} /* namespace solid */
#endif /* OBB_H_ */
