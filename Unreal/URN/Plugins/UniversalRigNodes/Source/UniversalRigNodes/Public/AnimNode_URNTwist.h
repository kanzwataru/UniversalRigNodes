/*
* Copyright 2022 Denis Robert Patrut
* This code is licensed under the MIT license, check the LICENSE.txt in the repo root.
*/
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimNodeBase.h"
#include "BoneContainer.h"
#include "AnimNode_URNTwist.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct FTwistBoneEntry {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FBoneReference Bone;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.0, ClampMax = 1.0))
	float TwistBlend = 1.0f;
};

USTRUCT(BlueprintInternalUseOnly)
struct UNIVERSALRIGNODES_API FAnimNode_URNTwist : public FAnimNode_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FPoseLink Source;

	UPROPERTY(EditAnywhere, Category = Setup)
	FBoneReference TargetBone;

	UPROPERTY(EditAnywhere, Category = Setup)
	TArray<FTwistBoneEntry> TwistBones;
		
	// FAnimNode_Base interface begin
	virtual void Initialize_AnyThread(const FAnimationInitializeContext &Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext &Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext &Context) override;
	virtual void Evaluate_AnyThread(FPoseContext &Output) override;
	virtual void GatherDebugData(FNodeDebugData &DebugData) override;
	// FAnimNode_Base interface end
};
