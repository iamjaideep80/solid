#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include "SOP_Solid_Update_Sim.h"

#include "solid/core/SimData.h"
#include "../utils/BlindDataManager.h"
#include "../utils/AttribManager.h"
#include <iostream>
#include "../../solid/core/RigidBody.h"

using namespace HDK_Sample;
void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("solid_update_sim", "Solid Update Sim", SOP_Solid_Update_Sim::myConstructor,
							SOP_Solid_Update_Sim::myTemplateList, 1, 1, 0));
}

PRM_Template SOP_Solid_Update_Sim::myTemplateList[] =
{ PRM_Template(), };

OP_Node *
SOP_Solid_Update_Sim::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
	return new SOP_Solid_Update_Sim(net, name, op);
}

SOP_Solid_Update_Sim::SOP_Solid_Update_Sim(OP_Network *net, const char *name, OP_Operator *op) :
		SOP_Node(net, name, op)
{
}

SOP_Solid_Update_Sim::~SOP_Solid_Update_Sim()
{
}

OP_ERROR SOP_Solid_Update_Sim::cookMySop(OP_Context &context)
{
	gdp->clearAndDestroy();
	if (lockInputs(context) >= UT_ERROR_ABORT)
		return error();

	OP_Node::flags().timeDep = 1;
	CH_Manager *chman;
	chman = OPgetDirector()->getChannelManager();
	fpreal currframe = chman->getSample(context.getTime());

	duplicateSource(0, context);

	//Access Blind Data
	solid::houdini::BlindDataManager blindDataManager;
	solid::core::SimData* simDataPtr = blindDataManager.extractSimDataPtr(gdp);
	//Access Blind Data

	GEO_Point* ppt;
	int counter = 0;
	solid::houdini::AttribManager attribManager;
	GA_FOR_ALL_GPOINTS(gdp,ppt)
	{
		solid::core::RigidBody* rbdPtr = simDataPtr->rigidBodyVector[counter];

		solid::core::Vector3 forceVal;
		attribManager.getAttribValue(gdp, ppt, "force", forceVal);
		rbdPtr->force = forceVal;

		solid::core::Vector3 torqueVal;
		attribManager.getAttribValue(gdp, ppt, "torque", torqueVal);
		rbdPtr->torque = torqueVal;

		counter++;
	}
	gdp->destroyUnusedPoints();
	unlockInputs();
	return error();
}

const char *
SOP_Solid_Update_Sim::inputLabel(unsigned inum) const
{
	switch (inum)
	{
	case 0:
		return "Solid Sim";
	case 1:
		return "Prep Objects";
	}
	return "Unknown source";
}
