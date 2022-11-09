/*
* Copyright 2022 Denis Robert Patrut
* This code is licensed under the MIT license, check the LICENSE.txt in the repo root.
*/
#include "AnimNode_URNTwist.h"
#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"
#include "URN.h"

void FAnimNode_URNTwist::Initialize_AnyThread(const FAnimationInitializeContext &Context)
{
	FAnimNode_Base::Initialize_AnyThread(Context);
	Source.Initialize(Context);
}

void FAnimNode_URNTwist::CacheBones_AnyThread(const FAnimationCacheBonesContext &Context)
{
	Source.CacheBones(Context);

	const FBoneContainer &BoneContainer = Context.AnimInstanceProxy->GetRequiredBones();
	for(auto &Entry : TwistBones) {
		Entry.Bone.Initialize(BoneContainer);

		if(!Entry.Bone.IsValidToEvaluate(BoneContainer)) {
			// TODO: We may want to simply skip certain bones, instead of disabling altogether
			// TODO: Add a warning, and/or check in the blueprint compilation stage
			bIsValid = false;
		}
	}

	TargetBone.Initialize(BoneContainer);
	if(!TargetBone.IsValidToEvaluate(BoneContainer)) {
		// TODO: Add a warning, and/or check in the blueprint compilation stage
		bIsValid = false;
	}
}

void FAnimNode_URNTwist::Update_AnyThread(const FAnimationUpdateContext &Context)
{
	Source.Update(Context);
}

void FAnimNode_URNTwist::Evaluate_AnyThread(FPoseContext &Output)
{
	Source.Evaluate(Output);

	if(!FAnimWeight::IsRelevant(Alpha) || !bIsValid) {
		return;
	}

	const FBoneContainer& BoneContainer = Output.AnimInstanceProxy->GetRequiredBones();
	
	// TEMP: Just checking if the bones can be moved properly, for now
	const FMatrix TargetMatrix = Output.Pose[TargetBone.GetCompactPoseIndex(BoneContainer)].GetRotation().ToMatrix();
	for(auto &Entry : TwistBones) {
		auto BoneIdx = Entry.Bone.GetCompactPoseIndex(BoneContainer);

		auto &OutTransform = Output.Pose[BoneIdx];

		FMatrix OffsetMatrix;
		URN_calc_twist(&OffsetMatrix.M[0][0], &TargetMatrix.M[0][0], Entry.TwistBlend * Alpha);

		OutTransform.SetRotation(FQuat(OffsetMatrix)); // TODO PERF: Avoid conversion through quaternion
	}
}

void FAnimNode_URNTwist::GatherDebugData(FNodeDebugData &DebugData)
{
}
