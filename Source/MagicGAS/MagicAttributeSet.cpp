// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicAttributeSet.h"
#include "Net/UnrealNetwork.h"

UMagicAttributeSet::UMagicAttributeSet()
{
	
}

void UMagicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute()) 
	{
		NewValue = FMath::Clamp<float>(NewValue, 0, 100);
	}
}

void UMagicAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UMagicAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UMagicAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMagicAttributeSet, Health, OldHealth);
}
