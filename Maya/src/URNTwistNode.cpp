#include "URNTwistNode.h"
#include "MayaNodeIDs.h"

MTypeId URNTwistNode::typeId(URN_NODE_TWIST_ID);
MObject URNTwistNode::attr::inTargetLocalMatrix;
MObject URNTwistNode::attr::twist::inOffsetMatrix;
MObject URNTwistNode::attr::twist::inTwistPercent;
MObject URNTwistNode::attr::twist::outOffsetMatrix;
MObject URNTwistNode::attr::twistBones;

MStatus URNTwistNode::initialize()
{
	MStatus status = MStatus::kSuccess;
	MFnMatrixAttribute matrixAttr;
	MFnNumericAttribute numAttr;
	MFnCompoundAttribute compoundAttr;

	attr::inTargetLocalMatrix = matrixAttr.create("inTargetLocalMatrix", "itlm");
	matrixAttr.setReadable(false);
	matrixAttr.setWritable(true);
	matrixAttr.setStorable(false);
	VERIFY(addAttribute(attr::inTargetLocalMatrix));

	attr::twist::inTwistPercent = numAttr.create("inTwistPercent", "itp", MFnNumericData::Type::kFloat, 0.0);
	numAttr.setReadable(false);
	numAttr.setWritable(true);
	numAttr.setStorable(true);
	
	attr::twist::inOffsetMatrix = matrixAttr.create("inOffsetMatrix", "iom");
	matrixAttr.setReadable(true);
	matrixAttr.setWritable(true);
	matrixAttr.setStorable(true);

	attr::twist::outOffsetMatrix = matrixAttr.create("outOffsetMatrix", "oom");
	matrixAttr.setReadable(true);
	matrixAttr.setWritable(false);
	matrixAttr.setStorable(false);

	attr::twistBones = compoundAttr.create("twistBones", "tws");
	compoundAttr.setArray(true);
	VERIFY(compoundAttr.addChild(attr::twist::inTwistPercent));
	VERIFY(compoundAttr.addChild(attr::twist::inOffsetMatrix));
	VERIFY(compoundAttr.addChild(attr::twist::outOffsetMatrix));

	VERIFY(addAttribute(attr::twistBones));

	return status;
}

MStatus URNTwistNode::compute(const MPlug &plug, MDataBlock &data)
{
	MStatus status = MStatus::kSuccess;

	if(plug != attr::twistBones && plug != attr::twist::outOffsetMatrix) {
		return MStatus::kUnknownParameter;
	}

	MMatrix targetLocalMatrix = data.inputValue(attr::inTargetLocalMatrix).asMatrix();
	
	MArrayDataHandle twistBonesHandle = data.inputArrayValue(attr::twistBones);
	for(unsigned i = 0; i < twistBonesHandle.elementCount(); ++i, twistBonesHandle.next()) {
		// TODO: Implement...
	}

	return status;
}
