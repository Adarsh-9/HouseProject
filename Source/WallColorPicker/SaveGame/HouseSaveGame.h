// Copyright Adarsh S 2020

#pragma once

#include "CoreMinimal.h"
#include "LevelStruct.h"
#include "GameFramework/SaveGame.h"
#include "HouseSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class WALLCOLORPICKER_API UHouseSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame)
    FLevelStruct HouseSaveData;
};
