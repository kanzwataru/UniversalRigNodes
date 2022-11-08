/*
* Copyright 2022 Denis Robert Patrut
* This code is licensed under the MIT license, check the LICENSE.txt in the repo root.
*/
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnimNode_URNTwist.h"
#include "AnimGraphNode_Base.h"

#include "AnimGraphNode_URNTwist.generated.h"

UCLASS(MinimalAPI)
class UAnimGraphNode_URNTwist : public UAnimGraphNode_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_URNTwist BlendNode;

	// UEdGraphNode interface begin
	//virtual FLinearColor GetNodeTitleColor() const override;
	//virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString(TEXT("URNTwist")); }
	// UEdGraphNode interface end

	// UAnimGraphNode_Base interface begin
	virtual FString GetNodeCategory() const override { return TEXT("URN"); }
	// UAnimGraphNode_Base interface begin
};
