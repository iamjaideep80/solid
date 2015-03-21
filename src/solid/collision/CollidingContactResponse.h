/*
 * CollisionResponse.h
 *
 *  Created on: 18-Jul-2014
 *      Author: jaideep
 */

#ifndef COLLISIONRESPONSE_H_
#define COLLISIONRESPONSE_H_

#include "solid/core/CommonTypes.h"
#include "solid/core/RigidBody.h"
#include "CollisionPointInfo.h"
#include "ContactInfo.h"

namespace solid
{
	namespace collision
	{

		class CollidingContactResponse
		{
		public:
			CollidingContactResponse(ContactInfo contactInfo);
			virtual ~CollidingContactResponse();
			void modifyPosition();
			void modifyVelocity();
		private:
			ContactInfo contactInfo;
		};

	} /* namespace collision */
} /* namespace solid */
#endif /* COLLISIONRESPONSE_H_ */
