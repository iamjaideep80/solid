/*
 * HoudiniCgalGeomConverter.cpp
 *
 *  Created on: 30-May-2014
 *      Author: jaideep
 */

#include "HoudiniCgalGeomConverter.h"

namespace solid
{
	namespace houdini
	{
		namespace adapter
		{
			using namespace solid::geometry;

			HoudiniCgalGeomConverter::HoudiniCgalGeomConverter(GU_PrimPolySoup* soupPrimPtr,
					solid::geometry::Polyhedron* polyhedron)
			{
				std::vector<double> coords;
				std::vector<int> tris;
				HoudiniToIntermediate(soupPrimPtr, coords, tris);
				IntermediateToCgal(coords, tris, polyhedron);
			}

			HoudiniCgalGeomConverter::~HoudiniCgalGeomConverter()
			{
			}

			void HoudiniCgalGeomConverter::HoudiniToIntermediate(GU_PrimPolySoup* soupPrimPtr,
					std::vector<double>& coords, std::vector<int>& tris)
			{
				int vtxCount = soupPrimPtr->getVertexCount();
				for (int i = 0; i < vtxCount; i++)
				{
					GEO_Vertex vtx = soupPrimPtr->getVertex(i);
					UT_Vector3 pos = vtx.getPos3();
					coords.push_back(pos.x());
					coords.push_back(pos.y());
					coords.push_back(pos.z());
				}

				int polyCount = soupPrimPtr->getPolygonCount();
				for (int i = 0; i < polyCount; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						GA_Size start;
						GA_Size count;
						soupPrimPtr->getPolygonVertexRange(i, start, count);
						int vertextOffset = soupPrimPtr->getPolygonVertexOffset(i, j);
						GA_Size pointIndex = soupPrimPtr->findVertex(vertextOffset);
						tris.push_back(pointIndex);
					}
				}

			}

			void HoudiniCgalGeomConverter::IntermediateToCgal(std::vector<double>& coords,
					std::vector<int>& tris, solid::geometry::Polyhedron* polyhedron)
			{
				// build a polyhedron from the loaded arrays
				PolyhedronBuilder<HalfedgeDS> builder(coords, tris);
				polyhedron->delegate(builder);
			}

		} /* namespace adapter */
	} /* namespace houdini */
} /* namespace solid */
