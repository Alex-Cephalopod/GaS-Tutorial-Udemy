// Copyright Cephalo-Alex


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute(); //the property getter from the macro in AuraAttributeSet
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;//for this case, target and source are the same (the player)
	VigorDef.bSnapshot = false; //captures the value of the attribute at the time of creation if true, false when it is applied

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags; 
	EvaluationParameters.TargetTags = TargetTags;

	float VigorValue = 0;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, VigorValue);
	VigorValue = FMath::Max<float>(VigorValue, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 Level = CombatInterface->GetPlayerLevel();

	//Calculation can be whatever you want. for this project, max health is 
	// 80.f + 2.5f * vigor + 10.f * level

	return 80.f + 2.5f * VigorValue + 10.f * Level;
}
