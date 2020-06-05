//Copyright Adarsh S 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StyleCustomizationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WALLCOLORPICKER_API UStyleCustomizationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStyleCustomizationComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	TArray<UTexture2D*> UIImages;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	FName NameOfItem = "Item";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	float CostOfItem = 0.f;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials")
	TArray<class UMaterialInstance*> Materials;
	class MaterialInstanceDynamic* Dynamicmaterial = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Setup")
	bool bCanChangeColor = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	bool bCanChangeMaterial = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TArray<int32> MaterialIndices;
};
