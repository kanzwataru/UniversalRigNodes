#include "URNTwistNode.h"
#include "MayaNodeIDs.h"

MTypeId URNTwistNode::typeId(URN_NODE_TWIST_ID);
MObject URNTwistNode::attr::inTargetLocalMatrix;
MObject URNTwistNode::attr::inOffsetMatrix;
MObject URNTwistNode::attr::inTwistPercent;
MObject URNTwistNode::attr::outOffsetMatrix;

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

	attr::inTwistPercent = numAttr.create("inTwistPercent", "itp", MFnNumericData::Type::kFloat, 0.0);
	numAttr.setReadable(false);
	numAttr.setWritable(true);
	numAttr.setStorable(true);
	VERIFY(addAttribute(attr::inTwistPercent));
	
	attr::inOffsetMatrix = matrixAttr.create("inOffsetMatrix", "iom");
	matrixAttr.setReadable(true);
	matrixAttr.setWritable(true);
	matrixAttr.setStorable(true);
	VERIFY(addAttribute(attr::inOffsetMatrix));

	attr::outOffsetMatrix = matrixAttr.create("outOffsetMatrix", "oom");
	matrixAttr.setReadable(true);
	matrixAttr.setWritable(false);
	matrixAttr.setStorable(false);
	VERIFY(addAttribute(attr::outOffsetMatrix));

	attributeAffects(attr::inTargetLocalMatrix, attr::outOffsetMatrix);
	attributeAffects(attr::inTwistPercent, attr::outOffsetMatrix);
	attributeAffects(attr::inOffsetMatrix, attr::outOffsetMatrix);

	return status;
}

static double dot(const MVector &a, const MVector &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

MStatus URNTwistNode::compute(const MPlug &plug, MDataBlock &data)
{
	if(plug != attr::outOffsetMatrix) {
		return MStatus::kUnknownParameter;
	}

	const MMatrix targetLocalMatrix = data.inputValue(attr::inTargetLocalMatrix).asMatrix();
	const MMatrix inOffsetMatrix = data.inputValue(attr::inOffsetMatrix).asMatrix();
	const float twistPercent = data.inputValue(attr::inTwistPercent).asFloat();

#if 0
	// acos axis-angle implementation of lookat
	const MVector forward = targetLocalMatrix[0];
	const MVector axis = MVector(1.0f, 0.0f, 0.0f) ^ forward;
	const double angle = acos(dot(axis.normal(), MVector(1.0f, 0.0f, 0.0f)));

	const MMatrix outOffsetMatrix = MQuaternion(angle, axis).asMatrix() * inOffsetMatrix;
	//const MMatrix outOffsetMatrix = MQuaternion(angle, MVector(1.0f, 0.0f, 0.0f)).inverse().asMatrix() * inOffsetMatrix;
#else
	// Simple implementation of lookat
	const MVector forward = MVector(1.0f, 0.0f, 0.0f);
	const MVector up = targetLocalMatrix[2];
	const MVector across = (up ^ forward).normal();
	const MVector upOrtho = (forward ^ across).normal();

	const double offsetMatrixData[4][4] = {
		forward.x, forward.y, forward.z, 0.0f,
		across.x, across.y, across.z, 0.0f,
		upOrtho.x, upOrtho.y, upOrtho.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	const MMatrix offsetMatrix(offsetMatrixData);

	const MMatrix outOffsetMatrix = offsetMatrix * inOffsetMatrix;
#endif

	data.outputValue(attr::outOffsetMatrix).setMMatrix(outOffsetMatrix);

	return MStatus::kSuccess;
}
