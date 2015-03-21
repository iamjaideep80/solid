/*
 * RestingContactResponse.h
 *
 *  Created on: 01-Dec-2014
 *      Author: jaideep
 */

#ifndef RESTINGCONTACTRESPONSE_H_
#define RESTINGCONTACTRESPONSE_H_

#include "solid/core/CommonTypes.h"
#include <vector>
#include "../../solid/collision/ContactInfo.h"

namespace solid
{
	namespace collision
	{
		class RestingContactResponse
		{
		public:
			RestingContactResponse(std::vector<solid::collision::ContactInfo> restingContactList);
			virtual ~RestingContactResponse();
		private:
			void computeMatrixA();
			solid::core::Scalar computeAij(solid::collision::ContactInfo ci,
					solid::collision::ContactInfo cj);
			void computeVectorB();
			std::vector<solid::collision::ContactInfo> restingContactList;
			int numOfContacts;
			std::vector<std::vector<solid::core::Scalar> > matrixA;

		};

	} /* namespace collision */
} /* namespace solid */
#endif /* RESTINGCONTACTRESPONSE_H_ */
