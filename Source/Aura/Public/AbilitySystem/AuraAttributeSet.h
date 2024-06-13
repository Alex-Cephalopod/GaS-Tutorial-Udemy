// Copyright Cephalo-Alex

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties {

	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;

};

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; // Override to replicate attributes
	//Q: What is the purpose of this function?
	//A: This function is used to replicate the attributes of the attribute set. This is necessary to ensure that the attributes are synchronized across the network for multiplayer games.

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override; // Override to handle attribute changes before they occur

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override; // Override to handle gameplay effect execution

	/* Health attributes */
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes") // Replicated attribute using a rep notify
		FGameplayAttributeData Health; // Health attribute
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UFUNCTION() // Rep notify function. Can take no arguments or 1 argument of the same type as the attribute
		void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UFUNCTION()
		// Rep notify function for MaxHealth
		void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	/* Mana attributes */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Magic Attributes")
		FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UFUNCTION()
		void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Magic Attributes")
		FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	UFUNCTION()
		void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;


private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
