//Copyright Adarsh S 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HouseActor.generated.h"

UCLASS()
class WALLCOLORPICKER_API AHouseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHouseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
	class UMaterialInstanceDynamic* DynamicMaterial = nullptr;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box = nullptr;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UWidgetComponent* PromptWidget = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStyleCustomizationComponent* StyleCustomization = nullptr;
	UFUNCTION()
	void DisplayPrompt();
	UFUNCTION()
	void HidePrompt();
	UPROPERTY(BlueprintReadOnly)
	FLinearColor CurrentColor = FLinearColor(1,1,1,1);
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentMaterialindex = 0;
	UFUNCTION(BlueprintCallable, Category = "Style Change")
		void ChangeItemColor(FLinearColor NewColor);
	UFUNCTION(BlueprintCallable, Category = "Style Change")
		void ChangeItemMaterial(int32 index);
	UFUNCTION(BlueprintCallable, Category = "Save Game")
		void SaveSate();
	UFUNCTION(BlueprintCallable, Category = "Save Game")
		void LoadSate();
	UPROPERTY(BlueprintReadOnly)
		FString Namet = "";
	UPROPERTY(BlueprintReadOnly)
		FString FNamet = "";
private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
