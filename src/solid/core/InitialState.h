/*
 * InitialState.h
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#ifndef INITIALSTATE_H_
#define INITIALSTATE_H_

#include "CommonTypes.h"
#include "solid/core/AABB.h"

namespace solid
{
	namespace core
	{

		class InitialState
		{
		public:
			InitialState(Vector3 translation, Quaternion rotationQuaternion, Vector3 linearVelocity,
					Vector3 angularVelocity, AABB bbox, Scalar density, Matrix3 inertiaTensor, Scalar id,
					Scalar active, Scalar bounce);
			virtual ~InitialState();

			const Vector3& getAngularVelocity() const
			{
				return angularVelocity;
			}

			const Vector3& getLinearVelocity() const
			{
				return linearVelocity;
			}

			const Quaternion& getRotationQuaternion() const
			{
				return rotationQuaternion;
			}

			const Vector3& getTranslation() const
			{
				return translation;
			}

			const AABB& getBbox() const
			{
				return bbox;
			}

			Scalar getDensity() const
			{
				return density;
			}

			void setDensity(Scalar density)
			{
				this->density = density;
			}

			const Matrix3& getInertiaTensor() const
			{
				return inertiaTensor;
			}

			void setInertiaTensor(const Matrix3& inertiaTensor)
			{
				this->inertiaTensor = inertiaTensor;
			}

			Scalar getId() const
			{
				return id;
			}

			void setId(Scalar id)
			{
				this->id = id;
			}

			Scalar getActive() const
			{
				return active;
			}

			void setActive(Scalar active)
			{
				this->active = active;
			}

			Scalar getBounce() const
			{
				return bounce;
			}

			void setBounce(Scalar bounce)
			{
				this->bounce = bounce;
			}

		private:
			Vector3 translation;
			Quaternion rotationQuaternion;
			Vector3 linearVelocity;
			Vector3 angularVelocity;
			AABB bbox;
			Scalar density;
			Scalar bounce;
			Matrix3 inertiaTensor;
			Scalar id;
			Scalar active;
		};

	} /* namespace core */
} /* namespace solid */
#endif /* INITIALSTATE_H_ */
