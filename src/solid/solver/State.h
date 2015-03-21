/*
 * State.h
 *
 *  Created on: 04-May-2014
 *      Author: jaideep
 */

#ifndef STATE_H_
#define STATE_H_

#include "solid/core/CommonTypes.h"

namespace solid
{
	namespace solver
	{
		class State
		{
		public:
			State();
			virtual ~State();
			solid::core::Vector3 translation;
			solid::core::Quaternion rotationQuaternion;
			solid::core::Vector3 linearMomentum;
			solid::core::Vector3 angularMomentum;
		};
	} /* namespace core */
} /* namespace solid */
#endif /* STATE_H_ */
