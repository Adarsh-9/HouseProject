// Copyright Adarsh S 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HouseActorDataStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct WALLCOLORPICKER_API FHouseActorDataStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame)
	FLinearColor Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame)
	int32 MaterialIndex;
};
