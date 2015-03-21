/*
 * InitialState.cpp
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#include "InitialState.h"
#include <iostream>
namespace solid
{
	namespace core
	{

		InitialState::InitialState(Vector3 translation, Quaternion rotationQuaternion, Vector3 linearVelocity,
				Vector3 angularVelocity, AABB bbox, Scalar density, Matrix3 inertiaTensor, Scalar id,
				Scalar active,Scalar bounce) :
				translation(translation), rotationQuaternion(rotationQuaternion),
						linearVelocity(linearVelocity), angularVelocity(angularVelocity), bbox(bbox),
						density(density), inertiaTensor(inertiaTensor), id(id), active(active),bounce(bounce)
		{
		}

		InitialState::~InitialState()
		{
		}

	} /* namespace core */
} /* namespace solid */
