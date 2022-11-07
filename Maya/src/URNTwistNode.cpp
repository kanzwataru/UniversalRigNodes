/*
 * Copyright 2022 Denis Robert Patrut
 * This code is licensed under the MIT license, check the LICENSE.txt in the repo root.
*/
#include "URNTwistNode.h"
#include "MayaNodeIDs.h"
#include "UniversalRigNodes.h"

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

	attr::inTargetLocalMatrix = matrixAttr.create("inTargetLocalMatrix", "itlm", MFnMatrixAttribute::kFloat);
	matrixAttr.setReadable(false);
	matrixAttr.setWritable(true);
	matrixAttr.setStorable(false);
	VERIFY(addAttribute(attr::inTargetLocalMatrix));

	attr::inTwistPercent = numAttr.create("inTwistPercent", "itp", MFnNumericData::Type::kFloat, 0.0);
	numAttr.setReadable(false);
	numAttr.setWritable(true);
	numAttr.setStorable(true);
	VERIFY(addAttribute(attr::inTwistPercent));
	
	attr::inOffsetMatrix = matrixAttr.create("inOffsetMatrix", "iom", MFnMatrixAttribute::kFloat);
	matrixAttr.setReadable(true);
	matrixAttr.setWritable(true);
	matrixAttr.setStorable(true);
	VERIFY(addAttribute(attr::inOffsetMatrix));

	attr::outOffsetMatrix = matrixAttr.create("outOffsetMatrix", "oom", MFnMatrixAttribute::kFloat);
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

	const MFloatMatrix targetLocalMatrix = data.inputValue(attr::inTargetLocalMatrix).asFloatMatrix();
	const MFloatMatrix inOffsetMatrix = data.inputValue(attr::inOffsetMatrix).asFloatMatrix();
	const float twistPercent = data.inputValue(attr::inTwistPercent).asFloat();

#if 0
	// Simple implementation of lookat-based twist
	const MVector forward = MVector(1.0f, 0.0f, 0.0f);
	const MVector up = targetLocalMatrix[2];
	const MVector across = (up ^ forward).normal();
	const MVector upOrtho = (forward ^ across).normal();

	const double rotMatrixData[4][4] = {
		forward.x, forward.y, forward.z, 0.0f,
		across.x, across.y, across.z, 0.0f,
		upOrtho.x, upOrtho.y, upOrtho.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	const MFloatMatrix rotMatrix(rotMatrixData);
	const MQuaternion rot = MTransformationMatrix(rotMatrix).rotation();
	const MEulerRotation rotEuler = rot.asEulerRotation();
	const MEulerRotation finalRotEuler(rotEuler.x * double(twistPercent), 0.0, 0.0);

	const MFloatMatrix offsetMatrix = finalRotEuler.asMatrix();
#else
	MFloatMatrix offsetMatrix;
	URN_calc_twist(&offsetMatrix[0][0], &targetLocalMatrix[0][0], twistPercent);
#endif

	const MFloatMatrix outOffsetMatrix = offsetMatrix * inOffsetMatrix;

	data.outputValue(attr::outOffsetMatrix).setMFloatMatrix(outOffsetMatrix);

	return MStatus::kSuccess;
}
