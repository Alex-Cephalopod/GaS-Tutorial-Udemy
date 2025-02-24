// Copyright Cephalo-Alex


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag) // or Info.AttributeTag.MatchesTagExact(AttributeTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("AttributeInfo for Tag %s not found in %s"), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
