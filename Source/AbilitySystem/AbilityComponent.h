#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityType.h"
#include "AbilityComponent.generated.h"

/**
 * Component responsible for managing character abilities: combat, support, movement, control, etc.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class YOURGAME_API UAbilityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAbilityComponent();

protected:
    virtual void BeginPlay() override;

public:
    // ------------------ Ability Access ------------------

    /** Get data of a combat ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Combat")
    FAbilityData GetCombatAbility(ECombatAbility Ability) const;

    /** Get data of a support ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Support")
    FAbilityData GetSupportAbility(ESupportAbility Ability) const;

    /** Get data of a movement ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Movement")
    FAbilityData GetMovementAbility(EMovementAbility Ability) const;

    /** Get data of a control ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Control")
    FAbilityData GetControlAbility(EControlAbility Ability) const;

    // ------------------ Ability State ------------------

    /** Check if a combat ability is unlocked */
    UFUNCTION(BlueprintCallable, Category = "Ability|Combat")
    bool IsCombatAbilityUnlocked(ECombatAbility Ability) const;

    /** Check if a support ability is unlocked */
    UFUNCTION(BlueprintCallable, Category = "Ability|Support")
    bool IsSupportAbilityUnlocked(ESupportAbility Ability) const;

    /** Check if a movement ability is unlocked */
    UFUNCTION(BlueprintCallable, Category = "Ability|Movement")
    bool IsMovementAbilityUnlocked(EMovementAbility Ability) const;

    /** Check if a control ability is unlocked */
    UFUNCTION(BlueprintCallable, Category = "Ability|Control")
    bool IsControlAbilityUnlocked(EControlAbility Ability) const;

    // ------------------ Ability Management ------------------

    /** Unlock a combat ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Combat")
    void UnlockCombatAbility(ECombatAbility Ability);

    /** Unlock a support ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Support")
    void UnlockSupportAbility(ESupportAbility Ability);

    /** Unlock a movement ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Movement")
    void UnlockMovementAbility(EMovementAbility Ability);

    /** Unlock a control ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Control")
    void UnlockControlAbility(EControlAbility Ability);

    /** Upgrade a combat ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Combat")
    void UpgradeCombatAbility(ECombatAbility Ability);

    /** Upgrade a support ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Support")
    void UpgradeSupportAbility(ESupportAbility Ability);

    /** Upgrade a movement ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Movement")
    void UpgradeMovementAbility(EMovementAbility Ability);

    /** Upgrade a control ability */
    UFUNCTION(BlueprintCallable, Category = "Ability|Control")
    void UpgradeControlAbility(EControlAbility Ability);

protected:

    // ------------------ Storage ------------------

    /** Combat ability map */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities|Combat")
    TMap<ECombatAbility, FAbilityData> CombatAbilities;

    /** Support ability map */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities|Support")
    TMap<ESupportAbility, FAbilityData> SupportAbilities;

    /** Movement ability map */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities|Movement")
    TMap<EMovementAbility, FAbilityData> MovementAbilities;

    /** Control ability map */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities|Control")
    TMap<EControlAbility, FAbilityData> ControlAbilities;

private:

    /** Safely upgrade ability level */
    void ApplyUpgrade(FAbilityData& Ability);

    /** Internal unlock logic */
    void ApplyUnlock(FAbilityData& Ability);
};
