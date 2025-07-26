#include "AbilityComponent.h"

UAbilityComponent::UAbilityComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAbilityComponent::BeginPlay()
{
    Super::BeginPlay();
}

// ------------------ Access ------------------

FAbilityData UAbilityComponent::GetCombatAbility(ECombatAbility Ability) const
{
    const FAbilityData* Found = CombatAbilities.Find(Ability);
    return Found ? *Found : FAbilityData();
}

FAbilityData UAbilityComponent::GetSupportAbility(ESupportAbility Ability) const
{
    const FAbilityData* Found = SupportAbilities.Find(Ability);
    return Found ? *Found : FAbilityData();
}

FAbilityData UAbilityComponent::GetMovementAbility(EMovementAbility Ability) const
{
    const FAbilityData* Found = MovementAbilities.Find(Ability);
    return Found ? *Found : FAbilityData();
}

FAbilityData UAbilityComponent::GetControlAbility(EControlAbility Ability) const
{
    const FAbilityData* Found = ControlAbilities.Find(Ability);
    return Found ? *Found : FAbilityData();
}

// ------------------ Unlock Checks ------------------

bool UAbilityComponent::IsCombatAbilityUnlocked(ECombatAbility Ability) const
{
    if (const FAbilityData* Found = CombatAbilities.Find(Ability))
    {
        return Found->bUnlocked;
    }
    return false;
}

bool UAbilityComponent::IsSupportAbilityUnlocked(ESupportAbility Ability) const
{
    if (const FAbilityData* Found = SupportAbilities.Find(Ability))
    {
        return Found->bUnlocked;
    }
    return false;
}

bool UAbilityComponent::IsMovementAbilityUnlocked(EMovementAbility Ability) const
{
    if (const FAbilityData* Found = MovementAbilities.Find(Ability))
    {
        return Found->bUnlocked;
    }
    return false;
}

bool UAbilityComponent::IsControlAbilityUnlocked(EControlAbility Ability) const
{
    if (const FAbilityData* Found = ControlAbilities.Find(Ability))
    {
        return Found->bUnlocked;
    }
    return false;
}

// ------------------ Unlock ------------------

void UAbilityComponent::UnlockCombatAbility(ECombatAbility Ability)
{
    if (FAbilityData* Found = CombatAbilities.Find(Ability))
    {
        ApplyUnlock(*Found);
    }
}

void UAbilityComponent::UnlockSupportAbility(ESupportAbility Ability)
{
    if (FAbilityData* Found = SupportAbilities.Find(Ability))
    {
        ApplyUnlock(*Found);
    }
}

void UAbilityComponent::UnlockMovementAbility(EMovementAbility Ability)
{
    if (FAbilityData* Found = MovementAbilities.Find(Ability))
    {
        ApplyUnlock(*Found);
    }
}

void UAbilityComponent::UnlockControlAbility(EControlAbility Ability)
{
    if (FAbilityData* Found = ControlAbilities.Find(Ability))
    {
        ApplyUnlock(*Found);
    }
}

// ------------------ Upgrade ------------------

void UAbilityComponent::UpgradeCombatAbility(ECombatAbility Ability)
{
    if (FAbilityData* Found = CombatAbilities.Find(Ability))
    {
        ApplyUpgrade(*Found);
    }
}

void UAbilityComponent::UpgradeSupportAbility(ESupportAbility Ability)
{
    if (FAbilityData* Found = SupportAbilities.Find(Ability))
    {
        ApplyUpgrade(*Found);
    }
}

void UAbilityComponent::UpgradeMovementAbility(EMovementAbility Ability)
{
    if (FAbilityData* Found = MovementAbilities.Find(Ability))
    {
        ApplyUpgrade(*Found);
    }
}

void UAbilityComponent::UpgradeControlAbility(EControlAbility Ability)
{
    if (FAbilityData* Found = ControlAbilities.Find(Ability))
    {
        ApplyUpgrade(*Found);
    }
}

// ------------------ Internal ------------------

void UAbilityComponent::ApplyUnlock(FAbilityData& Ability)
{
    Ability.bUnlocked = true;
}

void UAbilityComponent::ApplyUpgrade(FAbilityData& Ability)
{
    if (Ability.bUnlocked)
    {
        int32 Current = static_cast<int32>(Ability.Level);
        int32 Max = static_cast<int32>(EAbilityLevel::Max);
        if (Current < Max)
        {
            Ability.Level = static_cast<EAbilityLevel>(Current + 1);
        }
    }
}
