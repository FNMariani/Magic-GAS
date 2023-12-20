// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthArea.generated.h"

UCLASS()
class MAGICGAS_API AHealthArea : public AActor
{
	GENERATED_BODY()
	
public:
	AHealthArea();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void Heal();

private:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess=true)) 	
	class UBoxComponent* BoxComponent = nullptr;

	FTimerHandle RecoverHealthTimerHandle;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> RecoverHealthGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Healing)
	float HealInterval = 1.0f;
};
