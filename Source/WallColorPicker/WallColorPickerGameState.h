// Copyright Adarsh S 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Actors/HouseActor.h"
#include "WallColorPickerGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FObjectModified,AHouseActor*,HouseActor);
UCLASS()
class WALLCOLORPICKER_API AWallColorPickerGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FObjectModified ObjectModified;
	
};
