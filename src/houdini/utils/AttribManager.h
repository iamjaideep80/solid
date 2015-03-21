/*
 * AttribManager.h
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#ifndef ATTRIBMANAGER_H_
#define ATTRIBMANAGER_H_

#include "GU/GU_Detail.h"
#include "solid/core/CommonTypes.h"

namespace solid
{
	namespace houdini
	{
		class AttribManager
		{
		public:
			AttribManager();
			virtual ~AttribManager();
			bool getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
					UT_Vector3& val);
			bool getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
					UT_Vector4& val);
			bool getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
					solid::core::Scalar& val);
			bool getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
					solid::core::Vector3& val);
			bool getAttribValue(const GU_Detail* gdp, const GEO_Point* point, const char* name,
					solid::core::Vector3& val);
			bool getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
					solid::core::Quaternion& val);
			bool getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
					solid::core::Matrix3& val);
		};

	} /* namespace houdini */
} /* namespace solid */
#endif /* ATTRIBMANAGER_H_ */
