//Copyright Adarsh S 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectSelectionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WALLCOLORPICKER_API UObjectSelectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectSelectionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void Interact();

public:
	UPROPERTY(BlueprintReadOnly)
	class AHouseActor* ModifyingActor = nullptr;
private:
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	UPrimitiveComponent* PreviousComponent = nullptr;
	class AHouseActor* PreviousActor = nullptr;
	FHitResult HitResult;
	bool bDisplayColors = false;
	bool bDisplayTextures = false;
};
