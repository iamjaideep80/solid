/*
 * HoudiniCgalGeomConverter.h
 *
 *  Created on: 30-May-2014
 *      Author: jaideep
 */

#ifndef HOUDINICGALGEOMCONVERTER_H_
#define HOUDINICGALGEOMCONVERTER_H_

#include "GU/GU_Detail.h"
#include "solid/geometry/Polyhedron.h"
#include "solid/geometry/PolyhedronBuilder.h"
#include "GU/GU_PrimPolySoup.h"

namespace solid
{
	namespace houdini
	{
		namespace adapter
		{
			class HoudiniCgalGeomConverter
			{
			public:
				HoudiniCgalGeomConverter(GU_PrimPolySoup* soupPrimPtr,
						solid::geometry::Polyhedron* polyhedron);
				virtual ~HoudiniCgalGeomConverter();
			private:
				void HoudiniToIntermediate(GU_PrimPolySoup* soupPrimPtr, std::vector<double>& coords,
						std::vector<int>& tris);
				void IntermediateToCgal(std::vector<double>& coords, std::vector<int>& tris,
						solid::geometry::Polyhedron* polyhedron);
			};
		} /* namespace adapter */
	} /* namespace houdini */
} /* namespace solid */
#endif /* HOUDINICGALGEOMCONVERTER_H_ */
