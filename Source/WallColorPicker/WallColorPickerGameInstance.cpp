// Copyright Adarsh S 2020


#include "WallColorPickerGameInstance.h"
#include "SaveGame/HouseSaveGame.h"
#include "kismet/GameplayStatics.h"


void UWallColorPickerGameInstance::Init()
{
	Super::Init();
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		SaveGame = Cast<UHouseSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	}
	else
	{
		SaveGame = Cast<UHouseSaveGame>(UGameplayStatics::CreateSaveGameObject(UHouseSaveGame::StaticClass()));
	}
}
