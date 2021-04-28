#pragma once
#include "Player/CharacterPlayerState.h"

class Utils
{
public:
    template <typename T>
    static T* GetPlayerComponent(AActor* Pawn)
    {
        if (!Pawn) return nullptr;

        const auto Component = Pawn->GetComponentByClass(T::StaticClass());
        const auto Casted = Cast<T>(Component);
        return Casted;
    }

    bool static AreEnemies(AController* One, AController* Two)
    {
        if (!One || !Two || One == Two) return false;

        const auto State1 = Cast<ACharacterPlayerState>(One->PlayerState);
        const auto State2 = Cast<ACharacterPlayerState>(Two->PlayerState);

        return State1 && State2 && State1->GetTeamID() != State2->GetTeamID();
    }
};
