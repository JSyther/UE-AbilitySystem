#pragma once

#include "CoreMinimal.h"
#include "AbilityType.generated.h"

/** Combat-focused abilities */
UENUM(BlueprintType)
enum class ECombatAbility : uint8
{
    None        UMETA(DisplayName = "None"),
    Melee       UMETA(DisplayName = "Melee"),
    Ranged      UMETA(DisplayName = "Ranged"),
    Charge      UMETA(DisplayName = "Charge"),
    Overdrive   UMETA(DisplayName = "Overdrive")
};

/** Support and utility abilities */
UENUM(BlueprintType)
enum class ESupportAbility : uint8
{
    None        UMETA(DisplayName = "None"),
    Heal        UMETA(DisplayName = "Heal"),
    Shield      UMETA(DisplayName = "Shield"),
    Cleanse     UMETA(DisplayName = "Cleanse"),
    Revive      UMETA(DisplayName = "Revive")
};

/** Movement and mobility abilities */
UENUM(BlueprintType)
enum class EMovementAbility : uint8
{
    None        UMETA(DisplayName = "None"),
    Dash        UMETA(DisplayName = "Dash"),
    Teleport    UMETA(DisplayName = "Teleport"),
    WallRun     UMETA(DisplayName = "WallRun"),
    Grapple     UMETA(DisplayName = "Grapple")
};

/** Crowd control or elemental abilities */
UENUM(BlueprintType)
enum class EControlAbility : uint8
{
    None        UMETA(DisplayName = "None"),
    Stun        UMETA(DisplayName = "Stun"),
    Freeze      UMETA(DisplayName = "Freeze"),
    Burn        UMETA(DisplayName = "Burn"),
    Slow        UMETA(DisplayName = "Slow")
};

/** Ability data struct */
USTRUCT(BlueprintType)
struct FAbilityData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cooldown = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EnergyCost = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUnlocked = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;
};
