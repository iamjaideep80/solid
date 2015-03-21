/*
 * PolyhedronCollisionDetector.h
 *
 *  Created on: 31-May-2014
 *      Author: jaideep
 */

#ifndef POLYHEDRONCOLLISIONDETECTOR_H_
#define POLYHEDRONCOLLISIONDETECTOR_H_

#include "../geometry/Polyhedron.h"
#include "solid/core/CommonTypes.h"
#include "solid/core/Range.h"
#include "CollisionState.h"
namespace solid
{
	namespace collision
	{

		class PolyhedronCollisionDetector
		{
		public:
			PolyhedronCollisionDetector(solid::geometry::Polyhedron* geomA,
					solid::geometry::Polyhedron* geomB);
			virtual ~PolyhedronCollisionDetector();
			bool TestCollision(CollisionPointInfo & info);

		private:

			solid::geometry::Polyhedron* geomA;
			solid::geometry::Polyhedron* geomB;
			bool testWithPolygonNormals(solid::geometry::Polyhedron* geom, CollisionPointInfo & info);
			solid::core::Vector3 calculateFaceNormal(solid::geometry::Polyhedron::Facet_iterator facetItr);
			bool testWithDirection(solid::core::Vector3 dir, CollisionPointInfo & info);
			solid::core::Range getRange(solid::geometry::Polyhedron* geom, solid::core::Vector3 dir);
		};
	} /* namespace collision */
} /* namespace solid */
#endif /* POLYHEDRONCOLLISIONDETECTOR_H_ */
