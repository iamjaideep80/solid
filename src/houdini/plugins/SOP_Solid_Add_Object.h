#ifndef __SOP_Solid_Add_Object_h__
#define __SOP_Solid_Add_Object_h__
#include <SOP/SOP_Node.h>
#define INT_PARM(name, idx, vidx, t)	\
	    return evalInt(name, &myOffsets[idx], vidx, t);
#define FLT_PARM(name, idx, vidx, t)	\
	    return evalFloat(name, &myOffsets[idx], vidx, t);
namespace HDK_Sample
{
	class SOP_Solid_Add_Object : public SOP_Node
	{
	public:
		SOP_Solid_Add_Object(OP_Network *net, const char *name, OP_Operator *op);
		virtual ~SOP_Solid_Add_Object();
		static PRM_Template myTemplateList[];
		static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
	protected:
		virtual const char *inputLabel(unsigned idx) const;
		virtual OP_ERROR cookMySop(OP_Context &context);
	private:
		const GU_Detail* sourceObjGdp;
	};
} // End HDK_Sample namespace
#endif
