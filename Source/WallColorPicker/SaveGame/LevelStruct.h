// Copyright Adarsh S 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Actors/HouseActor.h"
#include "HouseActorDataStruct.h"
#include "LevelStruct.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct WALLCOLORPICKER_API FLevelStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame)
		TMap<FString, FHouseActorDataStruct> HouseActor;
};
