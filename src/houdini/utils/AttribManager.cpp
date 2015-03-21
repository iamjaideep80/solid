/*
 * AttribManager.cpp
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#include "AttribManager.h"

namespace solid
{
	namespace houdini
	{

		AttribManager::AttribManager()
		{
		}

		AttribManager::~AttribManager()
		{
		}

		bool AttribManager::getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
				UT_Vector3& val)
		{
			GA_ROAttributeRef attRef_type = gdp->findNumericTuple(GA_ATTRIB_PRIMITIVE, name, 3, 3);
			if (attRef_type.isValid())
				prim->get(attRef_type, val.data(), 3);
			return attRef_type.isValid();
		}

		bool AttribManager::getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
				UT_Vector4& val)
		{
			GA_ROAttributeRef attRef_type = gdp->findNumericTuple(GA_ATTRIB_PRIMITIVE, name, 4, 4);
			if (attRef_type.isValid())
				prim->get(attRef_type, val.data(), 4);
			return attRef_type.isValid();
		}

		bool AttribManager::getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
				solid::core::Scalar& val)
		{
			GA_ROAttributeRef attRef_type = gdp->findNumericTuple(GA_ATTRIB_PRIMITIVE, name, 1, 1);
			if (attRef_type.isValid())
				prim->get(attRef_type, val, 0);
			return attRef_type.isValid();
		}
		bool AttribManager::getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
				solid::core::Vector3& val)
		{
			GA_ROAttributeRef attRef_type = gdp->findNumericTuple(GA_ATTRIB_PRIMITIVE, name, 3, 3);
			if (attRef_type.isValid())
				prim->get(attRef_type, val.data(), 3);
			return attRef_type.isValid();
		}
		bool AttribManager::getAttribValue(const GU_Detail* gdp, const GEO_Point* point, const char* name,
				solid::core::Vector3& val)
		{
			GA_ROAttributeRef attRef_type = gdp->findNumericTuple(GA_ATTRIB_POINT, name, 3, 3);
			if (attRef_type.isValid())
				point->get(attRef_type, val.data(), 3);
			return attRef_type.isValid();
		}
		bool AttribManager::getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
				solid::core::Quaternion& val)
		{
			GA_ROAttributeRef attRef_type = gdp->findNumericTuple(GA_ATTRIB_PRIMITIVE, name, 4, 4);
			double array[4];
			if (attRef_type.isValid())
				prim->get(attRef_type, array, 4);
			val.w() = array[3];
			val.x() = array[0];
			val.y() = array[1];
			val.z() = array[2];
			return attRef_type.isValid();
		}
		bool AttribManager::getAttribValue(const GU_Detail* gdp, const GEO_Primitive* prim, const char* name,
				solid::core::Matrix3& val)
		{
			GA_ROAttributeRef attRef_type = gdp->findNumericTuple(GA_ATTRIB_PRIMITIVE, name, 9, 9);
			double array[9];
			if (attRef_type.isValid())
				prim->get(attRef_type, array, 9);
			val << array[0], array[1], array[2], array[3], array[4], array[5], array[6], array[7], array[8];
			return attRef_type.isValid();
		}
	} /* namespace houdini */
} /* namespace solid */
