// Copyright Adarsh S 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WallColorPickerController.generated.h"

/**
 * 
 */
UCLASS()
class WALLCOLORPICKER_API AWallColorPickerController : public APlayerController
{
	GENERATED_BODY()
public:
    AWallColorPickerController();
    void BeginPlay() override;
};
