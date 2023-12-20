// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoverHealthGameplayEffect.h"
#include "MagicAttributeSet.h"

URecoverHealthGameplayEffect::URecoverHealthGameplayEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	Modifiers.SetNum(1);

	FGameplayModifierInfo& Info = Modifiers[0];
	Info.ModifierMagnitude = FScalableFloat(20.0f);
	Info.ModifierOp = EGameplayModOp::Additive;
	Info.Attribute = UMagicAttributeSet::GetHealthAttribute();
}
