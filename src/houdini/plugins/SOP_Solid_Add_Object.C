#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include "SOP_Solid_Add_Object.h"

#include "solid/core/SimData.h"
#include "../utils/BlindDataManager.h"
#include "../adapter/AddObjectAdapter.h"
#include <iostream>

using namespace HDK_Sample;
void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("solid_add_object", "Solid Add Object", SOP_Solid_Add_Object::myConstructor,
							SOP_Solid_Add_Object::myTemplateList, 2, 2, 0));
}

PRM_Template SOP_Solid_Add_Object::myTemplateList[] =
{ PRM_Template(), };

OP_Node *
SOP_Solid_Add_Object::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
	return new SOP_Solid_Add_Object(net, name, op);
}

SOP_Solid_Add_Object::SOP_Solid_Add_Object(OP_Network *net, const char *name, OP_Operator *op) :
		SOP_Node(net, name, op)
{
	sourceObjGdp = NULL;
}

SOP_Solid_Add_Object::~SOP_Solid_Add_Object()
{
}

OP_ERROR SOP_Solid_Add_Object::cookMySop(OP_Context &context)
{
	gdp->clearAndDestroy();
	if (lockInputs(context) >= UT_ERROR_ABORT)
		return error();

	OP_Node::flags().timeDep = 1;
	CH_Manager *chman;
	chman = OPgetDirector()->getChannelManager();
	fpreal currframe = chman->getSample(context.getTime());

	duplicateSource(0, context);
	sourceObjGdp = inputGeo(1);

	//Access Blind Data
	solid::houdini::BlindDataManager blindDataManager;
	solid::core::SimData* simDataPtr = blindDataManager.extractSimDataPtr(gdp);
	//Access Blind Data

	if (currframe <= simDataPtr->getResetFrame())
	{
		solid::houdini::adapter::AddObjectAdapter adapter(simDataPtr, sourceObjGdp);
		adapter.addObjectsToSim();
	}

	unlockInputs();
	return error();
}

const char *
SOP_Solid_Add_Object::inputLabel(unsigned inum) const
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
