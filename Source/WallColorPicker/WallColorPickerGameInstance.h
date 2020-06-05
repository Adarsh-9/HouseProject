// Copyright Adarsh S 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WallColorPickerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WALLCOLORPICKER_API UWallColorPickerGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "SaveGame")
        class UHouseSaveGame* SaveGame = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGame")
        FString SlotName = "HouseData";
    virtual void Init() override;
};
