#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include "SOP_Solid_Houdini_To_CGAL.h"

#include <iostream>
#include "../adapter/HoudiniCgalGeomConverter.h"

#include<CGAL/Simple_cartesian.h>
#include<CGAL/Polyhedron_incremental_builder_3.h>
#include<CGAL/Polyhedron_3.h>
#include<CGAL/IO/Polyhedron_iostream.h>

#include "GU/GU_PrimPolySoup.h"

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream
typedef CGAL::Simple_cartesian<double> Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Polyhedron::HalfedgeDS HalfedgeDS;

using namespace HDK_Sample;
void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("solid_houdini_to_cgal", "Solid Houdini To CGAL",
							SOP_Solid_Houdini_To_CGAL::myConstructor,
							SOP_Solid_Houdini_To_CGAL::myTemplateList, 1, // Min required sources
							1,	// Maximum sources
							0));
}

static PRM_Name names[] =
{ PRM_Name("reset", "Reset Frame"), PRM_Name("subSteps", "Sub Steps"), PRM_Name("sim_time_scale",
																				"Simulation Time Scale"), };

static PRM_Default defaultSubSteps(1);

PRM_Template SOP_Solid_Houdini_To_CGAL::myTemplateList[] =
{ PRM_Template(PRM_INT, 1, &names[0], PRMoneDefaults), PRM_Template(PRM_INT_J, 1, &names[1],
																	&defaultSubSteps),
	PRM_Template(PRM_FLT, 1, &names[2], PRMoneDefaults), PRM_Template(), };

int * SOP_Solid_Houdini_To_CGAL::myOffsets = 0;

OP_Node *
SOP_Solid_Houdini_To_CGAL::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
	return new SOP_Solid_Houdini_To_CGAL(net, name, op);
}

SOP_Solid_Houdini_To_CGAL::SOP_Solid_Houdini_To_CGAL(OP_Network *net, const char *name, OP_Operator *op) :
		SOP_Node(net, name, op)
{
	if (!myOffsets)
		myOffsets = allocIndirect(32);
	myLastCookTime = 0;
	simDataPtr = NULL;
}

SOP_Solid_Houdini_To_CGAL::~SOP_Solid_Houdini_To_CGAL()
{
//	delete simDataPtr;
}

OP_ERROR SOP_Solid_Houdini_To_CGAL::cookMySop(OP_Context &context)
{
	gdp->clearAndDestroy();
	if (lockInputs(context) >= UT_ERROR_ABORT)
		return error();

	duplicateSource(0, context);

	int counter = 0;
	GEO_Primitive* primPtr;
	int vtxOffset = 0;
	GA_FOR_ALL_PRIMITIVES(gdp,primPtr)
	{
		GU_PrimPolySoup* soupPrimPtr = (GU_PrimPolySoup*) primPtr;
		Polyhedron polyhedron;
		solid::houdini::adapter::HoudiniCgalGeomConverter converter(soupPrimPtr, &polyhedron);

		vtxOffset = vtxOffset + primPtr->getVertexCount();
		// write the polyhedron out as a .OFF file
//		std::stringstream sstm;
//		sstm << "/home/jaideep/Desktop/dump_" << counter << ".off";
		char numstr[200]; // enough to hold all numbers up to 64-bits
		sprintf(numstr, "/home/jaideep/Desktop/dump_%d.off", counter);
		std::ofstream os(numstr);
//		std::ofstream os("/home/jaideep/Desktop/dump_0.off");
		os << polyhedron;
		os.close();
		counter++;
	}

	unlockInputs();
	return error();
}
