/*
 * Copyright 2022 Denis Robert Patrut
 * This code is licensed under the MIT license, check the LICENSE.txt in the repo root.
*/
#include "URNTwistNode.h"
#include "MayaNodeIDs.h"
#include "URN.h"

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

	attr::inTwistPercent = numAttr.create("inTwistPercent", "itp", MFnNumericData::Type::kDouble, 0.5);
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
	const double twistPercent = data.inputValue(attr::inTwistPercent).asDouble();

	MMatrix offsetMatrix;
	URN_calc_twist(&offsetMatrix[0][0], &targetLocalMatrix[0][0], twistPercent);

	const MMatrix outOffsetMatrix = offsetMatrix * inOffsetMatrix;

	data.outputValue(attr::outOffsetMatrix).setMMatrix(outOffsetMatrix);

	return MStatus::kSuccess;
}
