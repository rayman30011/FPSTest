#pragma once

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
};
