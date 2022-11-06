/*
 *	URNTwistNode
 * A simple node for calculating twist bone rotations.
 * 
 * ---------------------------------------------------------------------------------------
 * Copyright 2022 Denis Robert Patrut
 * This code is licensed under the MIT license, check the LICENSE.txt in the repo root.
*/
#pragma once
#include "MayaCommon.h"

class URNTwistNode : public MPxNode
{
	struct attr {
		static MObject inTargetLocalMatrix;		// The local matrix of the target joint (e.g. wrist)

		struct twist {
			static MObject inTwistPercent;		// The amount (in 0.0 - 1.0) to apply the target's rotation.
			static MObject inOffsetMatrix;		// If this controller has another procedural node affecting it, connect it here.
			static MObject outOffsetMatrix;		// The result of adding the twist, for connecting to offsetParentMatrix.
		};
		static MObject twistBones;
	};

public:
	static MTypeId typeId;

	static void *creator() { return new URNTwistNode; }
	static MStatus initialize();
	virtual MStatus	compute(const MPlug &plug, MDataBlock &data) override;
	virtual SchedulingType schedulingType() const { return SchedulingType::kParallel; }
};
