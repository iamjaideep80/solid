#ifndef __SOP_Solid_Solve_Sim_h__
#define __SOP_Solid_Solve_Sim_h__

#include <SOP/SOP_Node.h>

#include "solid/core/SimData.h"
#include "../adapter/SolveSimAdapter.h"

#define INT_PARM(name, idx, vidx, t)	\
	    return evalInt(name, &myOffsets[idx], vidx, t);
#define FLT_PARM(name, idx, vidx, t)	\
	    return evalFloat(name, &myOffsets[idx], vidx, t);
namespace HDK_Sample
{
	class SOP_Solid_Solve_Sim : public SOP_Node
	{
	public:
		SOP_Solid_Solve_Sim(OP_Network *net, const char *name, OP_Operator *op);
		virtual ~SOP_Solid_Solve_Sim();
		static PRM_Template myTemplateList[];
		static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
	protected:
		virtual const char *inputLabel(unsigned idx) const;
		void initSystem();
		virtual OP_ERROR cookMySop(OP_Context &context);
	private:
		int RESET()
		{
			INT_PARM("reset", 0, 0, 0)
		}
		int SUBSTEPS()
		{
			INT_PARM("subSteps", 2, 0, 0)
		}
		float SIM_TIME_SCALE()
		{
			return evalFloat("sim_time_scale", 0, 0);
		}
		fpreal myLastCookTime;	// Last cooked time
		static int *myOffsets;
		const GU_Detail* sourceGDP;
		solid::core::SimData* simDataPtr;
	};
} // End HDK_Sample namespace
#endif
