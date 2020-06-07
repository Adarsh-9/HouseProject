//Copyright Adarsh S 2020


#include "HouseActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "kismet/GameplayStatics.h"
#include "../WallColorPickerGameInstance.h"
#include "../SaveGame/HouseSaveGame.h"
#include "../SaveGame/LevelStruct.h"
#include "../SaveGame/HouseActorDataStruct.h"
//#include "DrawDebugHelpers.h"
#include "StyleCustomizationComponent.h"
#include "Engine.h"

// Sets default values
AHouseActor::AHouseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wall Mesh"));
	SetRootComponent(Cast<USceneComponent>(ItemMesh));
	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	Box->InitBoxExtent(FVector(10,10,10));
	Box->AttachToComponent(ItemMesh,FAttachmentTransformRules::KeepRelativeTransform,NAME_None);
	Box->SetGenerateOverlapEvents(true);
	Box->SetCollisionProfileName(FName("Trigger"));
	PromptWidget = CreateDefaultSubobject<UWidgetComponent>(FName("Prompt Widget"));
	PromptWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
	PromptWidget->SetWidgetSpace(EWidgetSpace::Screen);
	PromptWidget->SetDrawSize(FVector2D(400,100));
	PromptWidget->SetVisibility(false);
	
	StyleCustomization = CreateDefaultSubobject<UStyleCustomizationComponent>(FName("Style Component"));
	Namet = this->GetName();
	FNamet = this->GetFName().ToString();
}

// Called when the game starts or when spawned
void AHouseActor::BeginPlay()
{
	Super::BeginPlay();
	auto Material = ItemMesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	ItemMesh->SetMaterial(0, DynamicMaterial);
	//DrawDebugBox(GetWorld(),GetActorLocation(),Box->GetScaledBoxExtent(),FColor::White,true,0,0,5);
	ItemMesh->GetMaterial(0)->GetVectorParameterValue(FName("Color"),CurrentColor);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AHouseActor::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &AHouseActor::OnOverlapEnd);
}

void AHouseActor::ChangeItemColor(FLinearColor NewColor)
{
	DynamicMaterial->SetVectorParameterValue(FName("Color"),NewColor);
	CurrentColor = NewColor;
}

void AHouseActor::ChangeItemMaterial(int32 index)
{
	if (StyleCustomization->MaterialIndices.Num() > 1)
	{
		for (int32 mindex : StyleCustomization->MaterialIndices)
		{
			ItemMesh->SetMaterial(mindex, StyleCustomization->Materials[index]);
			CurrentMaterialindex = index;
		}
	}
	else if(StyleCustomization->MaterialIndices.Num() == 1)
	{
		ItemMesh->SetMaterial(StyleCustomization->MaterialIndices[0], StyleCustomization->Materials[index]);
		CurrentMaterialindex = index;
	}
	else
	{
		return;
	}
}



// Called every frame
void AHouseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHouseActor::DisplayPrompt()
{
	PromptWidget->SetVisibility(true);
	return;
}

void AHouseActor::HidePrompt()
{
	PromptWidget->SetVisibility(false);
	return;
}



void AHouseActor::LoadSate()
{
	auto SaveGame = Cast <UWallColorPickerGameInstance>(UGameplayStatics::GetGameInstance(this))->SaveGame;
	if (StyleCustomization->bCanChangeColor)
	{
		if (auto Result = SaveGame->HouseSaveData.HouseActor.Find(GetName()))
		{
			ChangeItemColor(Result->Color);
		}
	}
	else if (StyleCustomization->bCanChangeMaterial)
	{
		if (auto Result = SaveGame->HouseSaveData.HouseActor.Find(GetName()))
		{
			ChangeItemMaterial(Result->MaterialIndex);
		}
	}
}


void AHouseActor::SaveSate()
{
	auto SaveGame = Cast<UWallColorPickerGameInstance>(UGameplayStatics::GetGameInstance(this))->SaveGame;
	FString SlotName = Cast<UWallColorPickerGameInstance>(UGameplayStatics::GetGameInstance(this))->SlotName;
	if (StyleCustomization->bCanChangeColor)
	{
		FHouseActorDataStruct TempStruct;
		TempStruct.Color = CurrentColor;
		TempStruct.MaterialIndex = -1;
		SaveGame->HouseSaveData.HouseActor.Add(this->GetName(),TempStruct);
		UGameplayStatics::SaveGameToSlot(SaveGame,SlotName, 0);
	}
	else if (StyleCustomization->bCanChangeMaterial)
	{
		FHouseActorDataStruct TempStruct;
		TempStruct.Color = FLinearColor::Black;
		TempStruct.MaterialIndex = CurrentMaterialindex;
		SaveGame->HouseSaveData.HouseActor.Add(this->GetName(), TempStruct);
		UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, 0);
	}
}
void AHouseActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//PromptWidget->SetVisibility(true);
	}
}

void AHouseActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//PromptWidget->SetVisibility(false);
}