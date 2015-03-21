/*
 * RigidBody.cpp
 *
 *  Created on: 27-Apr-2014
 *      Author: jaideep
 */

#include "RigidBody.h"
#include <iostream>
#include "../geometry/Triangulation.h"

namespace solid
{
	namespace core
	{
		RigidBody::RigidBody()
		{
			objID = 0;
			density = 1000;
			mass = 1;
			bounce = 1;
			inertiaBodySpace.setIdentity();
			inertiaBodySpaceInverse.setIdentity();
			translation.setConstant(0);
			rotationQuaternion.setIdentity();
			rotationMatrix = rotationQuaternion.toRotationMatrix();
			linearVelocity = Vector3d(1, 0, 0);
			angularVelocity = Vector3d(1, 0, 0);
			inertia = rotationMatrix * inertiaBodySpace * rotationMatrix.transpose();
			linearMomentum = mass * linearVelocity;
			angularMomentum = inertia * angularVelocity;
			force.setConstant(0);
			torque.setConstant(0);
			active = true;
			volume = 1;
			collided = false;
			geomBodySpacePtr = NULL;
			geomWorldSpacePtr = NULL;
		}

		void RigidBody::initGeomPtrs(solid::geometry::Polyhedron* polyhedronPtr)
		{
			geomBodySpacePtr = polyhedronPtr;
			geomWorldSpacePtr = new solid::geometry::Polyhedron;
			*geomWorldSpacePtr = *geomBodySpacePtr;
		}

		RigidBody::RigidBody(InitialState initialState, solid::geometry::Polyhedron* polyhedronPtr)
		{
			objID = initialState.getId();
			active = initialState.getActive();
			translation = initialState.getTranslation();
			rotationQuaternion = initialState.getRotationQuaternion();
			linearVelocity = initialState.getLinearVelocity();
			angularVelocity = initialState.getAngularVelocity();
			aabbBodySpace = initialState.getBbox();
			collided = false;
			if (active == true)
			{
				density = initialState.getDensity();
			}
			else
			{
				density = 10000000;
			}
			volume = calculateVolume(polyhedronPtr);
			bounce = initialState.getBounce();
//			inertiaBodySpace = calculateInertiaBodySpace(polyhedronPtr);
			if (active == true)
			{
				inertiaBodySpace = initialState.getInertiaTensor();
			}
			else
			{
				inertiaBodySpace.setIdentity();
				inertiaBodySpace = inertiaBodySpace * 10000000;
			}

			initGeomPtrs(polyhedronPtr);
			calculateInitialDerivedParameters();
		}

		RigidBody::~RigidBody()
		{
		}

		void RigidBody::calculateInitialDerivedParameters()
		{
			mass = density * volume;
			rotationMatrix = rotationQuaternion.toRotationMatrix();
			linearMomentum = mass * linearVelocity;
			inertiaBodySpaceInverse = inertiaBodySpace.inverse();
			inertia = rotationMatrix * inertiaBodySpace * rotationMatrix.transpose();
			inertiaInverse = inertia.inverse();
			angularMomentum = inertia * angularVelocity;
			calculateAABBWorldSpace();
			calculateOBBWorldSpace();
			calculateGeometryWorldSpace();
		}

		void RigidBody::calculateAABBWorldSpace()
		{
			Vector3 cornerPos = aabbBodySpace.getCorner(solid::core::MIN, solid::core::MIN, solid::core::MIN);
			cornerPos = rotationMatrix * cornerPos + translation;
			AABB tempBBox(cornerPos, Vector3(0, 0, 0));
			cornerPos = aabbBodySpace.getCorner(solid::core::MIN, solid::core::MIN, solid::core::MAX);
			cornerPos = rotationMatrix * cornerPos + translation;
			tempBBox.expandUsingPoint(cornerPos);
			cornerPos = aabbBodySpace.getCorner(solid::core::MIN, solid::core::MAX, solid::core::MIN);
			cornerPos = rotationMatrix * cornerPos + translation;
			tempBBox.expandUsingPoint(cornerPos);
			cornerPos = aabbBodySpace.getCorner(solid::core::MIN, solid::core::MAX, solid::core::MAX);
			cornerPos = rotationMatrix * cornerPos + translation;
			tempBBox.expandUsingPoint(cornerPos);
			cornerPos = aabbBodySpace.getCorner(solid::core::MAX, solid::core::MIN, solid::core::MIN);
			cornerPos = rotationMatrix * cornerPos + translation;
			tempBBox.expandUsingPoint(cornerPos);
			cornerPos = aabbBodySpace.getCorner(solid::core::MAX, solid::core::MIN, solid::core::MAX);
			cornerPos = rotationMatrix * cornerPos + translation;
			tempBBox.expandUsingPoint(cornerPos);
			cornerPos = aabbBodySpace.getCorner(solid::core::MAX, solid::core::MAX, solid::core::MIN);
			cornerPos = rotationMatrix * cornerPos + translation;
			tempBBox.expandUsingPoint(cornerPos);
			cornerPos = aabbBodySpace.getCorner(solid::core::MAX, solid::core::MAX, solid::core::MAX);
			cornerPos = rotationMatrix * cornerPos + translation;
			tempBBox.expandUsingPoint(cornerPos);
			aabbWorldSpace = tempBBox;
		}

		void RigidBody::calculateOBBWorldSpace()
		{
			Vector3 centerPos = aabbBodySpace.getCenter();
			centerPos = rotationMatrix * centerPos + translation;
			Vector3 halfWidth = aabbBodySpace.getHalfWidth();
			Vector3 axis[3];
			axis[0].assign(1, 0, 0);
			axis[1].assign(0, 1, 0);
			axis[2].assign(0, 0, 1);
			for (int i = 0; i < 3; i++)
			{
				axis[i] = rotationMatrix * axis[i];
				axis[i].normalize();
			}
			OBB tempOBB(centerPos, halfWidth, axis);
			obbWorldSpace = tempOBB;
		}

		void RigidBody::calculateDerivedParameters()
		{
			linearVelocity = linearMomentum / mass;
			rotationMatrix = rotationQuaternion.toRotationMatrix();
			inertia = rotationMatrix * inertiaBodySpace * rotationMatrix.transpose();
			inertiaInverse = rotationMatrix * inertiaBodySpaceInverse * rotationMatrix.transpose();
//			inertiaInverse = inertia.inverse();
			angularVelocity = inertiaInverse * angularMomentum;
			calculateAABBWorldSpace();
			calculateOBBWorldSpace();
			calculateGeometryWorldSpace();
		}

		void RigidBody::calculateGeometryWorldSpace()
		{
			solid::geometry::Polyhedron::Vertex_iterator itrSrc;
			solid::geometry::Polyhedron::Vertex_iterator itrDest = geomWorldSpacePtr->vertices_begin();
			for (itrSrc = geomBodySpacePtr->vertices_begin(); itrSrc != geomBodySpacePtr->vertices_end();
					++itrSrc)
			{
				solid::geometry::Polyhedron::Point_3 pos = itrSrc->point();
				Vector3 bodySpacePos = Vector3(pos.x(), pos.y(), pos.z());
				Vector3 worldSpacePos;
				worldSpacePos = rotationMatrix * bodySpacePos + translation;
				itrDest->point() = solid::geometry::Polyhedron::Point_3(worldSpacePos[0], worldSpacePos[1],
																		worldSpacePos[2]);
				++itrDest;
			}
		}

		Scalar RigidBody::calculateVolume(solid::geometry::Polyhedron * polyhedronPtr)
		{
			solid::geometry::Triangulation T;
			solid::geometry::Polyhedron::Vertex_iterator itr;
			for (itr = polyhedronPtr->vertices_begin(); itr != polyhedronPtr->vertices_end(); ++itr)
			{
				solid::geometry::Polyhedron::Point_3 pos = itr->point();
				solid::geometry::Triangulation::Point posT(pos.x(), pos.y(), pos.z());
				T.insert(posT);
			}
//			solid::geometry::Triangulation::Point origin(0,0,0);
//			T.insert(origin);

			solid::geometry::Triangulation::Finite_cells_iterator itrCell;
			Scalar totalVolume = 0;
			for (itrCell = T.finite_cells_begin(); itrCell != T.finite_cells_end(); ++itrCell)
			{
				solid::geometry::Tetrahedron tet = T.tetrahedron(itrCell);
				totalVolume += tet.volume();
			}
			return totalVolume;
//			return 1;
		}
		Matrix3 RigidBody::calculateInertiaBodySpace(solid::geometry::Polyhedron * polyhedronPtr)
		{
			Matrix3 temp;
			temp.setIdentity();
			return temp;
		}
		Vector3 RigidBody::ptVelocity(solid::core::Vector3 pointPos)
		{
			Vector3 angularComp = angularVelocity.cross(pointPos - translation);
			return Vector3(linearVelocity + angularComp);
		}
	} /* namespace core */
} /* namespace solid */
