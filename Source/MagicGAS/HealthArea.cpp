// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthArea.h"
#include "MagicGASCharacter.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemComponent.h"
#include "RecoverHealthGameplayEffect.h"

AHealthArea::AHealthArea()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent, NAME_None);
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetBoxExtent(FVector(100.f, 100.f, 100.f), false);
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"), false);  

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHealthArea::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AHealthArea::OnOverlapEnd);
}

void AHealthArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHealthArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Display, TEXT("AHealthArea::OnOverlapBegin()"));

		if (!GetWorldTimerManager().IsTimerActive(RecoverHealthTimerHandle))
		{
			GetWorldTimerManager().SetTimer(RecoverHealthTimerHandle, this, &AHealthArea::Heal, HealInterval, true);
		}
	}
}

void AHealthArea::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Display, TEXT("AHealthArea::OnOverlapEnd()"));
	}
}

void AHealthArea::Heal()
{
	TSet<AActor*> TouchingActors;
	GetOverlappingActors(TouchingActors);

	for (AActor* const A : TouchingActors)
	{
		if (IsValid(A))
		{
			AMagicGASCharacter* OtherCharacter = Cast<AMagicGASCharacter>(A);
			if(OtherCharacter != nullptr)
			{
				UAbilitySystemComponent* ASC = OtherCharacter->GetAbilitySystemComponent();
				if(ASC != nullptr)
				{
					FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
					EffectContext.AddSourceObject(this);
					
					const UGameplayEffect* const EffectCDO = RecoverHealthGameplayEffect.GetDefaultObject();
					if(EffectCDO != nullptr)
					{
						ASC->ApplyGameplayEffectToSelf(EffectCDO, 1.0f, EffectContext);
					}
					else UE_LOG(LogTemp, Display, TEXT("EffectCDO NULL"));
				}
				else UE_LOG(LogTemp, Display, TEXT("ASC NULL"));
			}
			else UE_LOG(LogTemp, Display, TEXT("OtherCharacter NULL"));
		}
	}
	
	// Stop timer if nothing is overlapping
	if (TouchingActors.Num() == 0)
	{
		GetWorldTimerManager().ClearTimer(RecoverHealthTimerHandle);
	}
}