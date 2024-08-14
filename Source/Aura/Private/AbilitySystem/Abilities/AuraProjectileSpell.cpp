// Copyright Cephalo-Alex


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Actors/AuraProjectile.h"
#include "Interfaces/CombatInterface.h"

//#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//spawn projectile from the server
	bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation); 
		//TODO: Set Projectile rotation

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass, 
			SpawnTransform, 
			GetOwningActorFromActorInfo(), 
			Cast<APawn>(GetOwningActorFromActorInfo()), 
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn); 

		//TODO: Give projectile a Gameplay Effect Spec for causing damage

		Projectile->FinishSpawning(SpawnTransform);
	}
}

/*NOTES

#include "Kismet/KismetSystemLibrary.h"
UKismetSystemLibrary::PrintString(this, "Activate Ability! (C++)", true, true, FColor::Yellow, 3.f);


*/