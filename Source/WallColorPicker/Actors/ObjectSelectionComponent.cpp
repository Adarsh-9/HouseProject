//Copyright Adarsh S 2020


#include "ObjectSelectionComponent.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "../Actors/HouseActor.h"
#include "../Actors/StyleCustomizationComponent.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values for this component's properties
UObjectSelectionComponent::UObjectSelectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectSelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UObjectSelectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	auto LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * 500;
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Destructible),
		FCollisionQueryParams(FName(""), false, GetOwner())
	);
	//DrawDebugLine(GetWorld(),PlayerViewPointLocation,LineTraceEnd,FColor::White,false,0,0,2);
	if (HitResult.bBlockingHit)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Emerald, FString("You can edit the mesh"));
		if (!PreviousComponent)
		{
			PreviousComponent = HitResult.GetComponent();
			PreviousActor = Cast<AHouseActor>(HitResult.Actor);
			PreviousActor->DisplayPrompt();
			PreviousComponent->SetRenderCustomDepth(true);
		}
		if (PreviousComponent != HitResult.GetComponent())
		{
			PreviousComponent->SetRenderCustomDepth(false);
			PreviousActor->HidePrompt();
			HitResult.GetComponent()->SetRenderCustomDepth(true);
			Cast<AHouseActor>(HitResult.Actor)->DisplayPrompt();
			PreviousComponent = HitResult.GetComponent();
			PreviousActor = Cast<AHouseActor>(HitResult.Actor);
		}
		else if (PreviousComponent == HitResult.GetComponent())
		{
			HitResult.GetComponent()->SetRenderCustomDepth(true);
			Cast<AHouseActor>(HitResult.Actor)->DisplayPrompt();
			PreviousComponent = HitResult.GetComponent();
			PreviousActor = Cast<AHouseActor>(HitResult.Actor);
		}
	}
	else
	{
		Cast<ATP_ThirdPersonCharacter>(GetOwner())->DisplayColorUIElements(false);
		Cast<ATP_ThirdPersonCharacter>(GetOwner())->DisplayTextureUIElements(false);
		if (PreviousComponent)
		{
			PreviousComponent->SetRenderCustomDepth(false);
		}
		if (PreviousActor)
		{
			PreviousActor->HidePrompt();
		}
		//PreviousActor = nullptr;
		//PreviousComponent = nullptr;
	}
}

void UObjectSelectionComponent::Interact()
{
	if (HitResult.bBlockingHit)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Interaction initiated"));
		auto HitActor = Cast<AHouseActor>(HitResult.Actor);
		auto StyleComponent = HitActor->FindComponentByClass<UStyleCustomizationComponent>();
		bDisplayColors = StyleComponent->bCanChangeColor;
		bDisplayTextures = StyleComponent->bCanChangeMaterial;
		ModifyingActor = PreviousActor;
		Cast<ATP_ThirdPersonCharacter>(GetOwner())->DisplayTextureUIElements(bDisplayTextures);
		Cast<ATP_ThirdPersonCharacter>(GetOwner())->DisplayColorUIElements(bDisplayColors);
	}
}


