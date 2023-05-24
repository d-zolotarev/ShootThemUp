#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"

class STUUtils
{
public:
	template<typename T>
	FORCEINLINE static T* GetComponentByClass(const class APawn* const PlayerPawn)
	{
		return PlayerPawn ? Cast<T>(PlayerPawn->GetComponentByClass(T::StaticClass())) : nullptr;
	}
};
