/*
 * ContactType.h
 *
 *  Created on: 02-Jun-2014
 *      Author: jaideep
 */

#ifndef CONTACTTYPE_H_
#define CONTACTTYPE_H_

namespace solid
{
	namespace collision
	{
		enum ContactType
		{
			SEPARATING_CONTACT, COLLIDING_CONTACT, RESTING_CONTACT
		}
		;
	}
}

#endif /* COLLISIONSTATE_H_ */
