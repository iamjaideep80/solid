/*
 * RigidBody.h
 *
 *  Created on: 27-Apr-2014
 *      Author: jaideep
 */

#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "CommonTypes.h"
#include "InitialState.h"
#include "OBB.h"
#include "../geometry/Polyhedron.h"

namespace solid
{
//	namespace geometry
//	{
//		class Polyhedron;
//	}
	namespace core
	{
		class RigidBody
		{
		public:
			RigidBody();
			RigidBody(InitialState initialState, solid::geometry::Polyhedron* polyhedronPtr);
			virtual ~RigidBody();
		public:
			//Constant Quatities
			int objID;
			Scalar mass = 1.0;
			Scalar density;
			Scalar bounce;
			Scalar volume;
			Matrix3 inertiaBodySpace;
			Matrix3 inertiaBodySpaceInverse;
			//State Variables
			Vector3 translation;
			Quaternion rotationQuaternion;
			Vector3 linearMomentum;
			Vector3 angularMomentum;
			//Derived Quantities
			Matrix3 inertia;
			Matrix3 inertiaInverse;
			Matrix3 rotationMatrix;
			Vector3 linearVelocity;
			Vector3 angularVelocity;
			//Computed Quantities
			Vector3 force;
			Vector3 torque;
			bool active;
			//Geometry
			AABB aabbBodySpace;
			AABB aabbWorldSpace;
			OBB obbWorldSpace;
			bool collided;
			solid::geometry::Polyhedron* geomBodySpacePtr;
			solid::geometry::Polyhedron* geomWorldSpacePtr;
			void calculateDerivedParameters();
			Vector3 ptVelocity(Vector3 pointPos);
		private:
			void calculateInitialDerivedParameters();
			void calculateAABBWorldSpace();
			void calculateOBBWorldSpace();
			void calculateGeometryWorldSpace();
			void initGeomPtrs(solid::geometry::Polyhedron* polyhedronPtr);
			Scalar calculateVolume(solid::geometry::Polyhedron* polyhedronPtr);
			Matrix3 calculateInertiaBodySpace(solid::geometry::Polyhedron* polyhedronPtr);

		};

	} /* namespace core */
} /* namespace solid */
#endif /* RIGIDBODY_H_ */
