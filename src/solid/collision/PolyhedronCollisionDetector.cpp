/*
 * PolyhedronCollisionDetector.cpp
 *
 *  Created on: 31-May-2014
 *      Author: jaideep
 */

#include "PolyhedronCollisionDetector.h"
#include "CollisionPointInfo.h"

namespace solid
{
	namespace collision
	{
		using namespace solid::geometry;
		using namespace solid::core;
		PolyhedronCollisionDetector::PolyhedronCollisionDetector(solid::geometry::Polyhedron* geomA,
				solid::geometry::Polyhedron* geomB) :
				geomA(geomA), geomB(geomB)
		{
		}

		PolyhedronCollisionDetector::~PolyhedronCollisionDetector()
		{
		}

		bool PolyhedronCollisionDetector::TestCollision(CollisionPointInfo & info)
		{
			CollisionPointInfo infoA;
			if (!testWithPolygonNormals(geomA, infoA))
				return false;
			CollisionPointInfo infoB;
			if (!testWithPolygonNormals(geomB, infoB))
				return false;
			if (infoA.intersectionDist < infoB.intersectionDist)
			{
				info = infoA;
			}
			else
			{
				info = infoB;
			}
			return true;
		}
		bool PolyhedronCollisionDetector::testWithPolygonNormals(solid::geometry::Polyhedron* geom,
				CollisionPointInfo & info)
		{
			solid::geometry::Polyhedron::Facet_iterator facetItr;
//			Scalar minDist = 1000;
			CollisionPointInfo minInfo;
			minInfo.intersectionDist = 1000;
			for (facetItr = geom->facets_begin(); facetItr != geom->facets_end(); ++facetItr)
			{
				Vector3 normal = calculateFaceNormal(facetItr);
				Scalar tmpDist;
				CollisionPointInfo tmpInfo;
				if (!testWithDirection(normal, tmpInfo))
					return false;
				if (tmpInfo.intersectionDist < minInfo.intersectionDist)
					minInfo = tmpInfo;
			}
			info = minInfo;
			return true;
		}

		solid::core::Vector3 PolyhedronCollisionDetector::calculateFaceNormal(
				solid::geometry::Polyhedron::Facet_iterator facetItr)
		{
			Polyhedron::Point_3 v0 = facetItr->halfedge()->vertex()->point();
			Polyhedron::Point_3 v1 = facetItr->halfedge()->opposite()->vertex()->point();
			Polyhedron::Point_3 v2 = facetItr->halfedge()->next()->vertex()->point();
			Vector3 vtx0(v0.x(), v0.y(), v0.z());
			Vector3 vtx1(v1.x(), v1.y(), v1.z());
			Vector3 vtx2(v2.x(), v2.y(), v2.z());
			Vector3 vecA, vecB;
			vecA = vtx1 - vtx0;
			vecB = vtx2 - vtx1;
			Vector3 normal = vecA.cross(vecB);
			normal.normalize();
			return normal;
		}
		bool PolyhedronCollisionDetector::testWithDirection(solid::core::Vector3 dir,
				CollisionPointInfo & info)
		{
			solid::core::Range rangeA = getRange(geomA, dir);
			solid::core::Range rangeB = getRange(geomB, dir);
			Scalar tmpDist;
			CollisionPointInfo tmpInfo;
			bool intersecing = rangeA.testRangeCollision(rangeB, tmpInfo);
			if (intersecing)
				info = tmpInfo;
			return intersecing;
		}

		solid::core::Range PolyhedronCollisionDetector::getRange(solid::geometry::Polyhedron* geom,
				solid::core::Vector3 dir)
		{
			Polyhedron::Vertex_iterator vtxItr = geom->vertices_begin();
			Vector3 vtxPos(vtxItr->point().x(), vtxItr->point().y(), vtxItr->point().z());
			Scalar projection = dir.dot(vtxPos);
			Range range(dir, vtxPos);

			for (vtxItr = geom->vertices_begin(); vtxItr != geom->vertices_end(); ++vtxItr)
			{
				Vector3 vtxPos(vtxItr->point().x(), vtxItr->point().y(), vtxItr->point().z());
//				Scalar projection = dir.dot(vtxPos);
				range.addToRange(vtxPos);
			}
			return range;
		}

	} /* namespace collision */
} /* namespace solid */
