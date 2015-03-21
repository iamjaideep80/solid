/*
 * CollisionState.h
 *
 *  Created on: 02-Jun-2014
 *      Author: jaideep
 */

#ifndef COLLISIONSTATE_H_
#define COLLISIONSTATE_H_

namespace solid
{
	namespace collision
	{
		enum CollisionState
		{
			NO_CONTACT, CONTACT, DEEP_INTERSECTION
		}
		;
	}
}

#endif /* COLLISIONSTATE_H_ */
