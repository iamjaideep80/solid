/*
 * RigidBodyPointConverter.cpp
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#include "RigidBodyPointConverter.h"

namespace solid
{
	namespace houdini
	{
		namespace adapter
		{

			RigidBodyPointConverter::RigidBodyPointConverter()
			{
			}

			RigidBodyPointConverter::~RigidBodyPointConverter()
			{
			}

			void RigidBodyPointConverter::convertRigidBodyToPoint(solid::core::RigidBody* rigidBodyPtr,
					GU_Detail* gdp, GEO_Point* pointPtr)
			{
				pointPtr->setPos((double) rigidBodyPtr->translation[0], (double) rigidBodyPtr->translation[1],
									(double) rigidBodyPtr->translation[2]);

				GA_Offset ptoff = pointPtr->getMapOffset();

				GA_RWAttributeRef orientRef = gdp->addFloatTuple(GA_ATTRIB_POINT, "orient", 4);
				const GA_AIFTuple* orientRefTuple = orientRef.getAIFTuple();
				double array[4];
				array[0] = rigidBodyPtr->rotationQuaternion.x();
				array[1] = rigidBodyPtr->rotationQuaternion.y();
				array[2] = rigidBodyPtr->rotationQuaternion.z();
				array[3] = rigidBodyPtr->rotationQuaternion.w();
				orientRefTuple->set(orientRef.getAttribute(), ptoff, array, 4);

				GA_RWAttributeRef collidedRef = gdp->addFloatTuple(GA_ATTRIB_POINT, "collided", 1);
				const GA_AIFTuple* collidedRefTuple = collidedRef.getAIFTuple();
				float collided = rigidBodyPtr->collided;
				collidedRefTuple->set(collidedRef.getAttribute(), ptoff, &collided, 1);

				GA_RWAttributeRef massRef = gdp->addFloatTuple(GA_ATTRIB_POINT, "mass", 1);
				const GA_AIFTuple* massRefTuple = massRef.getAIFTuple();
				float mass = rigidBodyPtr->mass;
				massRefTuple->set(massRef.getAttribute(), ptoff, &mass, 1);

				GA_RWAttributeRef idRef = gdp->addFloatTuple(GA_ATTRIB_POINT, "id", 1);
				const GA_AIFTuple* idRefTuple = idRef.getAIFTuple();
				float id = rigidBodyPtr->objID;
				idRefTuple->set(idRef.getAttribute(), ptoff, &id, 1);

				GA_RWAttributeRef vRef = gdp->addFloatTuple(GA_ATTRIB_POINT, "v", 3);
				const GA_AIFTuple* vRefTuple = vRef.getAIFTuple();
				double arrayV[3];
				arrayV[0] = rigidBodyPtr->linearVelocity[0];
				arrayV[1] = rigidBodyPtr->linearVelocity[1];
				arrayV[2] = rigidBodyPtr->linearVelocity[2];
				vRefTuple->set(vRef.getAttribute(), ptoff, arrayV, 3);

				GA_RWAttributeRef fRef = gdp->addFloatTuple(GA_ATTRIB_POINT, "force", 3);
				const GA_AIFTuple* fRefTuple = fRef.getAIFTuple();
				double arrayF[3];
				arrayF[0] = rigidBodyPtr->force[0];
				arrayF[1] = rigidBodyPtr->force[1];
				arrayF[2] = rigidBodyPtr->force[2];
				fRefTuple->set(fRef.getAttribute(), ptoff, arrayF, 3);
			}

		} /* namespace converter */
	} /* namespace houdini */
} /* namespace solid */
