/*
 * CollisionDetectorSAT.cpp
 *
 *  Created on: 18-May-2014
 *      Author: jaideep
 */

#include "ObbCollisionDetector.h"
#include "solid/core/CommonTypes.h"
#include <iostream>
#include <cmath>

namespace solid
{
	namespace collision
	{

		ObbCollisionDetector::ObbCollisionDetector()
		{
		}

		ObbCollisionDetector::~ObbCollisionDetector()
		{
		}

		bool ObbCollisionDetector::TestCollision(solid::core::OBB& a, solid::core::OBB& b)
		{
			float ra, rb;
			solid::core::Matrix3 R, AbsR;
			// Compute rotation matrix expressing b in a’s coordinate frame
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					R(i, j) = a.u[i].dot(b.u[j]);

			// Compute translation vector t
			solid::core::Vector3 t;
			t[0] = b.c[0] - a.c[0];
			t[1] = b.c[1] - a.c[1];
			t[2] = b.c[2] - a.c[2];
//			solid::core::Vector3 t = b.c - a.c;
			// Bring translation into a’s coordinate frame
			t = solid::core::Vector3(t.dot(a.u[0]), t.dot(a.u[1]), t.dot(a.u[2]));
			// Compute common subexpressions. Add in an epsilon term to
			// counteract arithmetic errors when two edges are parallel and
			// their cross product is (near) null (see text for details)
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					AbsR(i, j) = std::abs((double) R(i, j)) + 0.01;
			// Test axes L = A0, L = A1, L = A2
			for (int i = 0; i < 3; i++)
			{
				ra = a.e[i];
				rb = b.e[0] * AbsR(i, 0) + b.e[1] * AbsR(i, 1) + b.e[2] * AbsR(i, 2);
				if (std::abs((double) t[i]) > ra + rb)
					return false;
			}
			// Test axes L = B0, L = B1, L = B2
			for (int i = 0; i < 3; i++)
			{
				ra = a.e[0] * AbsR(0, i) + a.e[1] * AbsR(1, i) + a.e[2] * AbsR(2, i);
				rb = b.e[i];
				if (std::abs((double) (t[0] * R(0, i) + t[1] * R(1, i) + t[2] * R(2, i))) > ra + rb)
					return false;
			}
			// Test axis L = A0 x B0
			ra = a.e[1] * AbsR(2, 0) + a.e[2] * AbsR(1, 0);
			rb = b.e[1] * AbsR(0, 2) + b.e[2] * AbsR(0, 1);
			if (std::abs((double) (t[2] * R(1, 0) - t[1] * R(2, 0))) > ra + rb)
				return false;
			// Test axis L = A0 x B1
			ra = a.e[1] * AbsR(2, 1) + a.e[2] * AbsR(1, 1);
			rb = b.e[0] * AbsR(0, 2) + b.e[2] * AbsR(0, 0);
			if (std::abs((double) (t[2] * R(1, 1) - t[1] * R(2, 1))) > ra + rb)
				return false;
			// Test axis L = A0 x B2
			ra = a.e[1] * AbsR(2, 2) + a.e[2] * AbsR(1, 2);
			rb = b.e[0] * AbsR(0, 1) + b.e[1] * AbsR(0, 0);
			if (std::abs((double) (t[2] * R(1, 2) - t[1] * R(2, 2))) > ra + rb)
				return false;
			// Test axis L = A1 x B0
			ra = a.e[0] * AbsR(2, 0) + a.e[2] * AbsR(0, 0);
			rb = b.e[1] * AbsR(1, 2) + b.e[2] * AbsR(1, 1);
			if (std::abs((double) (t[0] * R(2, 0) - t[2] * R(0, 0))) > ra + rb)
				return false;
			// Test axis L = A1 x B1
			ra = a.e[0] * AbsR(2, 1) + a.e[2] * AbsR(0, 1);
			rb = b.e[0] * AbsR(1, 2) + b.e[2] * AbsR(1, 0);
			if (std::abs((double) (t[0] * R(2, 1) - t[2] * R(0, 1))) > ra + rb)
				return false;
			// Test axis L = A1 x B2
			ra = a.e[0] * AbsR(2, 2) + a.e[2] * AbsR(0, 2);
			rb = b.e[0] * AbsR(1, 1) + b.e[1] * AbsR(1, 0);
			if (std::abs((double) (t[0] * R(2, 2) - t[2] * R(0, 2))) > ra + rb)
				return false;
			// Test axis L = A2 x B0
			ra = a.e[0] * AbsR(1, 0) + a.e[1] * AbsR(0, 0);
			rb = b.e[1] * AbsR(2, 2) + b.e[2] * AbsR(2, 1);
			if (std::abs((double) (t[1] * R(0, 0) - t[0] * R(1, 0))) > ra + rb)
				return false;
			// Test axis L = A2 x B1
			ra = a.e[0] * AbsR(1, 1) + a.e[1] * AbsR(0, 1);
			rb = b.e[0] * AbsR(2, 2) + b.e[2] * AbsR(2, 0);
			if (std::abs((double) (t[1] * R(0, 1) - t[0] * R(1, 1))) > ra + rb)
				return false;
			// Test axis L = A2 x B2
			ra = a.e[0] * AbsR(1, 2) + a.e[1] * AbsR(0, 2);
			rb = b.e[0] * AbsR(2, 1) + b.e[1] * AbsR(2, 0);
			if (std::abs((double) (t[1] * R(0, 2) - t[0] * R(1, 2))) > ra + rb)
				return false;

			// Since no separating axis is found, the OBBs must be intersecting
			return true;
		}

	} /* namespace collision */
} /* namespace solid */
