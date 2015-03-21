/*
 * AddObjectAdapter.cpp
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#include "AddObjectAdapter.h"
#include "../utils/AttribManager.h"
#include "solid/core/AABB.h"

#include "../../solid/core/RigidBody.h"
#include "../../solid/geometry/Polyhedron.h"
#include "../../solid/geometry/PolyhedronBuilder.h"
#include "../adapter/HoudiniCgalGeomConverter.h"

namespace solid
{
	namespace houdini
	{
		namespace adapter
		{

			AddObjectAdapter::AddObjectAdapter(solid::core::SimData* simDataPtr,
					const GU_Detail* sourceObjGdp) :
					simDataPtr(simDataPtr), sourceObjGdp(sourceObjGdp)
			{
			}

			AddObjectAdapter::~AddObjectAdapter()
			{
			}

			void AddObjectAdapter::addObjectsToSim()
			{
				int vtxOffset = 0;
				GEO_Primitive* primPtr;
				GA_FOR_ALL_PRIMITIVES(sourceObjGdp,primPtr)
				{
					GU_PrimPolySoup* soupPrimPtr = (GU_PrimPolySoup*) primPtr;
					solid::core::InitialState initState = extractInitialState(primPtr);

					UT_BoundingBox bbox;
					primPtr->getBBox(&bbox);

					solid::geometry::Polyhedron* polyhedronPtr = new solid::geometry::Polyhedron;
					solid::houdini::adapter::HoudiniCgalGeomConverter converter(soupPrimPtr, polyhedronPtr);
					vtxOffset = vtxOffset + soupPrimPtr->getVertexCount();
//					int count = simDataPtr->rigidBodyVector.size();
					solid::core::RigidBody* rigidBodyPtr = new solid::core::RigidBody(initState,
																						polyhedronPtr);
					simDataPtr->rigidBodyVector.push_back(rigidBodyPtr);
				}

			}

			solid::core::InitialState AddObjectAdapter::extractInitialState(const GEO_Primitive* primPtr)
			{
				solid::houdini::AttribManager attribManager;

				solid::core::Vector3 initPos;
				attribManager.getAttribValue(sourceObjGdp, primPtr, "initPos", initPos);

				solid::core::Quaternion orient(1, 0, 0, 0);
				attribManager.getAttribValue(sourceObjGdp, primPtr, "orient", orient);

				solid::core::Vector3 linearVelocity;
				attribManager.getAttribValue(sourceObjGdp, primPtr, "v", linearVelocity);

				solid::core::Vector3 angularVelocity;
				attribManager.getAttribValue(sourceObjGdp, primPtr, "angularVel", angularVelocity);

				solid::core::Scalar density;
				attribManager.getAttribValue(sourceObjGdp, primPtr, "density", density);

				solid::core::Scalar bounce;
				attribManager.getAttribValue(sourceObjGdp, primPtr, "bounce", bounce);

				solid::core::Scalar id;
				attribManager.getAttribValue(sourceObjGdp, primPtr, "id", id);

				solid::core::Scalar active;
				attribManager.getAttribValue(sourceObjGdp, primPtr, "active", active);

				solid::core::Matrix3 inertiaTensor;
				attribManager.getAttribValue(sourceObjGdp, primPtr, "inertiaTensor", inertiaTensor);

				UT_BoundingBox bboxHoudini;
				primPtr->getBBox(&bboxHoudini);
				solid::core::Vector3 center(bboxHoudini.centerX(), bboxHoudini.centerY(),
											bboxHoudini.centerZ());
				solid::core::Vector3 halfWidth(bboxHoudini.sizeX() * 0.5, bboxHoudini.sizeY() * 0.5,
												bboxHoudini.sizeZ() * 0.5);
				solid::core::AABB bboxSolid(center, halfWidth);

				return solid::core::InitialState(initPos, orient, linearVelocity, angularVelocity, bboxSolid,
													density, inertiaTensor, id, active, bounce);

			}

		} /* namespace adapter */
	} /* namespace houdini */
} /* namespace solid */
