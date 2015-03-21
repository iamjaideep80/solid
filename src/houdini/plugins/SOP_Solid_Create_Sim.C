#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include "SOP_Solid_Create_Sim.h"

#include "../utils/BlindDataManager.h"
#include <iostream>

using namespace HDK_Sample;
void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("solid_create_sim", "Solid Create Sim", SOP_Solid_Create_Sim::myConstructor,
							SOP_Solid_Create_Sim::myTemplateList, 0, // Min required sources
							0,	// Maximum sources
							0));
}

static PRM_Name names[] =
{ PRM_Name("reset", "Reset Frame"), PRM_Name("subSteps", "Sub Steps"), PRM_Name("maxSubSteps",
																				"Max Sub Steps"),
	PRM_Name("sim_time_scale", "Simulation Time Scale"), PRM_Name("collision_tolerance",
																	"Collision Tolerance") };

static PRM_Default defaultSubSteps(1);
static PRM_Default defaultMaxSubSteps(200);
static PRM_Default defaultCollTolerance(0.01);

PRM_Template SOP_Solid_Create_Sim::myTemplateList[] =
{ PRM_Template(PRM_INT, 1, &names[0], PRMoneDefaults), PRM_Template(PRM_INT_J, 1, &names[1],
																	&defaultSubSteps),
	PRM_Template(PRM_INT_J, 1, &names[2], &defaultMaxSubSteps), PRM_Template(PRM_FLT, 1, &names[3],
																				PRMoneDefaults),
	PRM_Template(PRM_FLT, 1, &names[4], &defaultCollTolerance), PRM_Template(), };

int * SOP_Solid_Create_Sim::myOffsets = 0;

OP_Node *
SOP_Solid_Create_Sim::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
	return new SOP_Solid_Create_Sim(net, name, op);
}

SOP_Solid_Create_Sim::SOP_Solid_Create_Sim(OP_Network *net, const char *name, OP_Operator *op) :
		SOP_Node(net, name, op)
{
	if (!myOffsets)
		myOffsets = allocIndirect(32);
	myLastCookTime = 0;
	simDataPtr = NULL;
}

SOP_Solid_Create_Sim::~SOP_Solid_Create_Sim()
{
//	delete simDataPtr;
}

void SOP_Solid_Create_Sim::initSystem()
{
//	std::cout << "Reset " << RESET() << std::endl;
//	std::cout << "Substeps " << SUBSTEPS() << std::endl;
//	std::cout << "Max Substeps " << MAX_SUBSTEPS() << std::endl;
//	std::cout << "Sim Time Scale " << SIM_TIME_SCALE() << std::endl;
	solid::houdini::BlindDataManager blindDataManager;
	gdp->clearAndDestroy();
	delete simDataPtr;
	simDataPtr = new solid::core::SimData(RESET(), SUBSTEPS(), MAX_SUBSTEPS(), SIM_TIME_SCALE(),
											COLLISION_TOLERANCE());
	blindDataManager.insertSimDataPtr(gdp, simDataPtr);
}

OP_ERROR SOP_Solid_Create_Sim::cookMySop(OP_Context &context)
{
	fpreal reset, currframe;
	CH_Manager *chman;
	if (lockInputs(context) >= UT_ERROR_ABORT)
		return error();
	OP_Node::flags().timeDep = 1;
	chman = OPgetDirector()->getChannelManager();
	currframe = chman->getSample(context.getTime());
	reset = RESET();
	if (currframe <= reset)
	{
		myLastCookTime = reset;
		initSystem();
	}
	unlockInputs();
	return error();
}
