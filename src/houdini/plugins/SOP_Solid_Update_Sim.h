#ifndef __SOP_Solid_Update_Sim_h__
#define __SOP_Solid_Update_Sim_h__
#include <SOP/SOP_Node.h>
#define INT_PARM(name, idx, vidx, t)	\
	    return evalInt(name, &myOffsets[idx], vidx, t);
#define FLT_PARM(name, idx, vidx, t)	\
	    return evalFloat(name, &myOffsets[idx], vidx, t);
namespace HDK_Sample
{
	class SOP_Solid_Update_Sim : public SOP_Node
	{
	public:
		SOP_Solid_Update_Sim(OP_Network *net, const char *name, OP_Operator *op);
		virtual ~SOP_Solid_Update_Sim();
		static PRM_Template myTemplateList[];
		static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
	protected:
		virtual const char *inputLabel(unsigned idx) const;
		virtual OP_ERROR cookMySop(OP_Context &context);
	};
} // End HDK_Sample namespace
#endif
