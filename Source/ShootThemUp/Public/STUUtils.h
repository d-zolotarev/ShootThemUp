#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "STUPlayerState.h"
#include "GameFramework/Controller.h"

class STUUtils
{
public:
	template<typename T>
	FORCEINLINE static T* GetComponentByClass(const class AActor* const PlayerPawn)
	{
		return PlayerPawn ? Cast<T>(PlayerPawn->GetComponentByClass(T::StaticClass())) : nullptr;
	}

	FORCEINLINE static bool AreEnemies(const AController* const Controller1, const AController* const Controller2)
	{
		if (!(Controller1 && Controller2) || Controller1 == Controller2) return false;

		const ASTUPlayerState* const PlayerState1 = Cast<ASTUPlayerState>(Controller1->PlayerState);
		const ASTUPlayerState* const PlayerState2 = Cast<ASTUPlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}
};
