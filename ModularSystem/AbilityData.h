/**
 * This data structure serves as a modular and extensible example designed primarily for educational purposes.
 * It offers a highly flexible framework that allows developers to easily add, modify, or remove ability categories
 * and related data without impacting the overall system architecture. 
 * Its design encourages scalability and adaptability, making it suitable for a wide range of use cases in ability management systems.
 * By leveraging this structure, users can experiment with and extend the concept of abilities in a clean, maintainable,
 * and reusable manner, thus fostering best practices in modular programming and data organization.
 */


/**
 * Compares two TMap containers for equality by checking if they contain the same key-value pairs.
 *
 * This function first verifies that the sizes of the two maps are equal. If they differ, the maps
 * are considered unequal immediately. Then it iterates through each key-value pair in the first map,
 * checking if the second map contains the same key with an equal value. If any key is missing or
 * any corresponding value differs, the function returns false.
 *
 * The comparison assumes that the ValueType supports the '!=' operator for equality checking.
 *
 * @tparam KeyType   The type of keys stored in the maps.
 * @tparam ValueType The type of values stored in the maps.
 * @param MapA       The first map to compare.
 * @param MapB       The second map to compare.
 * @return           True if both maps contain identical key-value pairs; otherwise false.
 */
template <typename KeyType, typename ValueType>
inline bool AreMapsEqual(const TMap<KeyType, ValueType>& MapA, const TMap<KeyType, ValueType>& MapB)
{
    // If the maps have different sizes, they are not equal
    if (MapA.Num() != MapB.Num())
    {
        return false;
    }

    // Iterate over MapA and check if all key-value pairs exist in MapB
    for (TPair<KeyType, ValueType>& PairA : MapA)
    {
        // Check if MapB contains the same key and value
        ValueType* ValueB = MapB.Find(PairA.Key);
        if (!ValueB || *ValueB != PairA.Value)
        {
            return false;
        }
    }

    // If all checks passed, the maps are equal
    return true;
}



/*
 * Encapsulates the current state and progression metrics of an individual ability.
 * Maintains the unlock status, active point count, maximum allowable points, and 
 * allocation of points from the character's overall pool.
 * Includes utility functions to safely modify points while ensuring consistent 
 * synchronization of the unlock state.
 */
USTRUCT(BlueprintType)
struct FAbilityModule
{
    GENERATED_BODY()

public:
    // Indicates whether the ability is unlocked.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
    bool bUnlocked = false;

    // Current active points assigned to the ability.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability", meta = (ClampMin = "0"))
    int8 Point = 0;

    // Maximum points allowed for this ability.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability", meta = (ClampMin = "1"))
    int8 MaxPoint = 5;

    // Points allocated from the character's total pool.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability", meta = (ClampMin = "0"))
    int8 AllocatedPoint = 0;

public:
    // Resets the ability to its default locked state with zero points.
    void Reset()
    {
        bUnlocked = false;
        Point = 0;
        AllocatedPoint = 0;
        MaxPoint = 5;
    }

    // Increases active points within allowed limits and updates unlock status.
    void IncreasePoint()
    {
        if (Point < MaxPoint && Point < AllocatedPoint)
        {
            ++Point;
            UpdateUnlockStatus();
        }
    }

    // Decreases active points if possible and updates unlock status.
    void DecreasePoint()
    {
        if (Point > 0)
        {
            --Point;
            UpdateUnlockStatus();
        }
    }

private:
    // Updates unlock status based on whether any points are active.
    void UpdateUnlockStatus()
    {
        bUnlocked = (Point > 0);
    }
};


UENUM(BlueprintType)
enum class EMagicalAbilityType : uint8
{
    Null                 UMETA(DisplayName = "Select Magical Ability"),
    Fireball             UMETA(DisplayName = "Fireball"),
    IceShield            UMETA(DisplayName = "Ice Shield"),
    LightningStrike      UMETA(DisplayName = "Lightning Strike"),
    ArcaneBlast          UMETA(DisplayName = "Arcane Blast"),
    HealingWave          UMETA(DisplayName = "Healing Wave"),
    Teleport             UMETA(DisplayName = "Teleport"),
    ManaSurge            UMETA(DisplayName = "Mana Surge"),
    FrostNova            UMETA(DisplayName = "Frost Nova"),
    Earthquake           UMETA(DisplayName = "Earthquake"),
    ShadowBolt           UMETA(DisplayName = "Shadow Bolt"),
    Max                  UMETA(Hidden)
};


USTRUCT(BlueprintType)
struct FMagicalAbility
{
    GENERATED_BODY()

protected:
    // Map storing magical abilities keyed by their enum type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    TMap<EMagicalAbilityType, FAbilityModule> MagicalAbilities;

public:
    // Constructor initializes the map with default ability modules for each ability type.
    FMagicalAbility()
    {
        for (uint8 i = static_cast<uint8>(EMagicalAbilityType::Null) + 1; i < static_cast<uint8>(EMagicalAbilityType::Max); ++i)
        {
            MagicalAbilities.Add(static_cast<EMagicalAbilityType>(i), FAbilityModule());
        }
    }

    // Equality operator compares the ability maps for equality.
    bool operator==(const FMagicalAbility& Other) const
    {
        return AreMapsEqual(MagicalAbilities, Other.MagicalAbilities);
    }

    // Inequality operator returns the negation of equality.
    bool operator!=(const FMagicalAbility& Other) const
    {
        return !(*this == Other);
    }

    // Returns a mutable reference to the magical abilities map.
    TMap<EMagicalAbilityType, FAbilityModule>& GetAbilities()
    {
        return MagicalAbilities;
    }

    // Returns a constant reference to the magical abilities map.
    const TMap<EMagicalAbilityType, FAbilityModule>& GetAbilities() const
    {
        return MagicalAbilities;
    }

    // Validates if the ability type exists in the map and logs errors if not.
    bool ValidateAbilityByType(EMagicalAbilityType Type) const
    {
        if (MagicalAbilities.IsEmpty())
        {
            UE_LOG(LogTemp, Error, TEXT("MagicalAbilities map is empty."));
            return false;
        }
        if (!MagicalAbilities.Contains(Type))
        {
            UE_LOG(LogTemp, Error, TEXT("Ability type not found in MagicalAbilities map."));
            return false;
        }
        return true;
    }

    // Resets the ability module associated with the given type to its default state.
    void ResetAbilityByType(EMagicalAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            MagicalAbilities[Type].Reset();
        }
    }

    // Increases the points for the specified ability type if valid.
    void IncreaseAbilityByType(EMagicalAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            MagicalAbilities[Type].IncreasePoint();
        }
    }

    // Decreases the points for the specified ability type if valid.
    void DecreaseAbilityByType(EMagicalAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            MagicalAbilities[Type].DecreasePoint();
        }
    }
};


UENUM(BlueprintType)
enum class ECraftingAbilityType : uint8
{
    Null                 UMETA(DisplayName = "Select Crafting Ability"),
    Blacksmithing        UMETA(DisplayName = "Blacksmithing"),
    Alchemy              UMETA(DisplayName = "Alchemy"),
    Carpentry            UMETA(DisplayName = "Carpentry"),
    Cooking              UMETA(DisplayName = "Cooking"),
    Tailoring            UMETA(DisplayName = "Tailoring"),
    Leatherworking       UMETA(DisplayName = "Leatherworking"),
    Jewelcrafting        UMETA(DisplayName = "Jewelcrafting"),
    Engineering          UMETA(DisplayName = "Engineering"),
    Enchanting           UMETA(DisplayName = "Enchanting"),
    Max                  UMETA(Hidden)
};
USTRUCT(BlueprintType)
struct FCraftingAbility
{
    GENERATED_BODY()

protected:
    // Map storing crafting abilities keyed by their enum type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    TMap<ECraftingAbilityType, FAbilityModule> CraftingAbilities;

public:
    // Constructor initializes the map with default ability modules for each crafting ability type.
    FCraftingAbility()
    {
        for (uint8 i = static_cast<uint8>(ECraftingAbilityType::Null) + 1; i < static_cast<uint8>(ECraftingAbilityType::Max); ++i)
        {
            CraftingAbilities.Add(static_cast<ECraftingAbilityType>(i), FAbilityModule());
        }
    }

    // Equality operator compares the crafting ability maps.
    bool operator==(const FCraftingAbility& Other) const
    {
        return AreMapsEqual(CraftingAbilities, Other.CraftingAbilities);
    }

    // Inequality operator returns the negation of equality.
    bool operator!=(const FCraftingAbility& Other) const
    {
        return !(*this == Other);
    }

    // Returns a mutable reference to the crafting abilities map.
    TMap<ECraftingAbilityType, FAbilityModule>& GetAbilities()
    {
        return CraftingAbilities;
    }

    // Returns a constant reference to the crafting abilities map.
    const TMap<ECraftingAbilityType, FAbilityModule>& GetAbilities() const
    {
        return CraftingAbilities;
    }

    // Validates if the specified crafting ability type exists in the map, logs error if not.
    bool ValidateAbilityByType(ECraftingAbilityType Type) const
    {
        if (CraftingAbilities.IsEmpty())
        {
            UE_LOG(LogTemp, Error, TEXT("CraftingAbilities map is empty."));
            return false;
        }
        if (!CraftingAbilities.Contains(Type))
        {
            UE_LOG(LogTemp, Error, TEXT("Ability type not found in CraftingAbilities map."));
            return false;
        }
        return true;
    }

    // Resets the crafting ability module at the specified type to default.
    void ResetAbilityByType(ECraftingAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            CraftingAbilities[Type].Reset();
        }
    }

    // Increases the point count for the specified crafting ability type.
    void IncreaseAbilityByType(ECraftingAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            CraftingAbilities[Type].IncreasePoint();
        }
    }

    // Decreases the point count for the specified crafting ability type.
    void DecreaseAbilityByType(ECraftingAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            CraftingAbilities[Type].DecreasePoint();
        }
    }
};


UENUM(BlueprintType)
enum class ESurvivalAbilityType : uint8
{
    Null                 UMETA(DisplayName = "Select Survival Ability"),
    Tracking             UMETA(DisplayName = "Tracking"),
    Foraging             UMETA(DisplayName = "Foraging"),
    ShelterBuilding      UMETA(DisplayName = "Shelter Building"),
    FireStarting         UMETA(DisplayName = "Fire Starting"),
    Hunting              UMETA(DisplayName = "Hunting"),
    Fishing              UMETA(DisplayName = "Fishing"),
    FirstAid             UMETA(DisplayName = "First Aid"),
    Navigation           UMETA(DisplayName = "Navigation"),
    WaterPurification    UMETA(DisplayName = "Water Purification"),
    Max                  UMETA(Hidden)
};
USTRUCT(BlueprintType)
struct FSurvivalAbility
{
    GENERATED_BODY()

protected:
    // Map holding survival abilities keyed by their enum type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    TMap<ESurvivalAbilityType, FAbilityModule> SurvivalAbilities;

public:
    // Constructor initializes the map with default ability modules for all survival ability types.
    FSurvivalAbility()
    {
        for (uint8 i = static_cast<uint8>(ESurvivalAbilityType::Null) + 1; i < static_cast<uint8>(ESurvivalAbilityType::Max); ++i)
        {
            SurvivalAbilities.Add(static_cast<ESurvivalAbilityType>(i), FAbilityModule());
        }
    }

    // Equality operator to compare survival abilities maps.
    bool operator==(const FSurvivalAbility& Other) const
    {
        return AreMapsEqual(SurvivalAbilities, Other.SurvivalAbilities);
    }

    // Inequality operator returns the negation of equality.
    bool operator!=(const FSurvivalAbility& Other) const
    {
        return !(*this == Other);
    }

    // Returns a mutable reference to the survival abilities map.
    TMap<ESurvivalAbilityType, FAbilityModule>& GetAbilities()
    {
        return SurvivalAbilities;
    }

    // Returns a constant reference to the survival abilities map.
    const TMap<ESurvivalAbilityType, FAbilityModule>& GetAbilities() const
    {
        return SurvivalAbilities;
    }

    // Validates whether the ability type exists in the survival abilities map.
    bool ValidateAbilityByType(ESurvivalAbilityType Type) const
    {
        if (SurvivalAbilities.IsEmpty())
        {
            UE_LOG(LogTemp, Error, TEXT("SurvivalAbilities map is empty."));
            return false;
        }
        if (!SurvivalAbilities.Contains(Type))
        {
            UE_LOG(LogTemp, Error, TEXT("Ability type not found in SurvivalAbilities map."));
            return false;
        }
        return true;
    }

    // Resets the specified survival ability to default.
    void ResetAbilityByType(ESurvivalAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            SurvivalAbilities[Type].Reset();
        }
    }

    // Increases points of the specified survival ability.
    void IncreaseAbilityByType(ESurvivalAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            SurvivalAbilities[Type].IncreasePoint();
        }
    }

    // Decreases points of the specified survival ability.
    void DecreaseAbilityByType(ESurvivalAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            SurvivalAbilities[Type].DecreasePoint();
        }
    }
};

UENUM(BlueprintType)
enum class EStealthAbilityType : uint8
{
    Null                 UMETA(DisplayName = "Select Stealth Ability"),
    Sneak                UMETA(DisplayName = "Sneak"),
    Pickpocket           UMETA(DisplayName = "Pickpocket"),
    Lockpicking          UMETA(DisplayName = "Lockpicking"),
    Backstab             UMETA(DisplayName = "Backstab"),
    Camouflage           UMETA(DisplayName = "Camouflage"),
    SilentMovement       UMETA(DisplayName = "Silent Movement"),
    Evasion              UMETA(DisplayName = "Evasion"),
    Disguise             UMETA(DisplayName = "Disguise"),
    TrapSetting          UMETA(DisplayName = "Trap Setting"),
    Max                  UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FStealthAbility
{
    GENERATED_BODY()

protected:
    // Map storing stealth abilities keyed by their enum type
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    TMap<EStealthAbilityType, FAbilityModule> StealthAbilities;

public:
    // Constructor initializes all stealth abilities with default modules
    FStealthAbility()
    {
        for (uint8 i = static_cast<uint8>(EStealthAbilityType::Null) + 1; i < static_cast<uint8>(EStealthAbilityType::Max); ++i)
        {
            StealthAbilities.Add(static_cast<EStealthAbilityType>(i), FAbilityModule());
        }
    }

    // Equality operator compares all stealth abilities for equality
    bool operator==(const FStealthAbility& Other) const
    {
        return AreMapsEqual(StealthAbilities, Other.StealthAbilities);
    }

    // Inequality operator returns negation of equality
    bool operator!=(const FStealthAbility& Other) const
    {
        return !(*this == Other);
    }

    // Returns mutable reference to the stealth abilities map
    TMap<EStealthAbilityType, FAbilityModule>& GetAbilities()
    {
        return StealthAbilities;
    }

    // Returns const reference to the stealth abilities map
    const TMap<EStealthAbilityType, FAbilityModule>& GetAbilities() const
    {
        return StealthAbilities;
    }

    // Validates if the given ability type exists in the map
    bool ValidateAbilityByType(EStealthAbilityType Type) const
    {
        if (StealthAbilities.IsEmpty())
        {
            UE_LOG(LogTemp, Error, TEXT("StealthAbilities map is empty."));
            return false;
        }
        if (!StealthAbilities.Contains(Type))
        {
            UE_LOG(LogTemp, Error, TEXT("Ability type not found in StealthAbilities map."));
            return false;
        }
        return true;
    }

    // Resets the specified ability to its default state
    void ResetAbilityByType(EStealthAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            StealthAbilities[Type].Reset();
        }
    }

    // Increments the point count for the specified ability
    void IncreaseAbilityByType(EStealthAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            StealthAbilities[Type].IncreasePoint();
        }
    }

    // Decrements the point count for the specified ability
    void DecreaseAbilityByType(EStealthAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            StealthAbilities[Type].DecreasePoint();
        }
    }
};


USTRUCT(BlueprintType)
struct FAbility
{
    GENERATED_BODY()

private:
    // Holds the character's martial abilities and their states.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FMartialAbility MartialAbility;
    
    // Holds the character's magical abilities and their states.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FMagicalAbility MagicalAbility;
    
    // Holds the character's crafting abilities and their states.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FCraftingAbility CraftingAbility;
    
    // Holds the character's survival abilities and their states.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FSurvivalAbility SurvivalAbility;
    
    // Holds the character's stealth abilities and their states.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FStealthAbility StealthAbility;
    
    // Total number of active ability points across all ability categories.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 AbilityPoints = 0;
    
    // Maximum allowed ability points the character can allocate.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 MaxAbilityPoints = 0;
    
    // Points allocated from the character's pool to various abilities.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 AllocatedPoints = 0;

public:
    // Equality operator: returns true if all ability categories and summary fields are equal.
    bool operator==(const FAbility& Other) const
    {
        return MartialAbility == Other.MartialAbility
            && MagicalAbility == Other.MagicalAbility
            && CraftingAbility == Other.CraftingAbility
            && SurvivalAbility == Other.SurvivalAbility
            && StealthAbility == Other.StealthAbility
            && AbilityPoints == Other.AbilityPoints
            && MaxAbilityPoints == Other.MaxAbilityPoints
            && AllocatedPoints == Other.AllocatedPoints;
    }
    
    // Inequality operator: returns true if any ability category or summary field differs.
    bool operator!=(const FAbility& Other) const
    {
        return !(*this == Other);
    }

    
    // Returns the total number of active ability points across all abilities.
    int32 GetAbilityPoints() const { return AbilityPoints; }
    
    // Returns the maximum allowed ability points the character can allocate.
    int32 GetMaxAbilityPoints() const { return MaxAbilityPoints; }
    
    // Returns the total points allocated from the character's pool to abilities.
    int32 GetAllocatedPoints() const { return AllocatedPoints; }
    
    // Setters for summary fields
    
    // Sets the total number of active ability points.
    void SetAbilityPoints(int32 NewPoints) { AbilityPoints = NewPoints; }
    
    // Sets the maximum allowed ability points.
    void SetMaxAbilityPoints(int32 NewMaxPoints) { MaxAbilityPoints = NewMaxPoints; }
    
    // Sets the total allocated points from the character's pool.
    void SetAllocatedPoints(int32 NewAllocatedPoints) { AllocatedPoints = NewAllocatedPoints; }
    
    // Getters for ability maps inside structs
    
    // Returns a mutable reference to the Martial abilities map.
    TMap<EMartialAbilityType, FAbilityModule>& GetMartialAbilities()
    {
        return MartialAbility.GetAbilities();
    }
    
    // Returns a const reference to the Martial abilities map.
    const TMap<EMartialAbilityType, FAbilityModule>& GetMartialAbilities() const
    {
        return MartialAbility.GetAbilities();
    }
    
    // Returns a mutable reference to the Magical abilities map.
    TMap<EMagicalAbilityType, FAbilityModule>& GetMagicalAbilities()
    {
        return MagicalAbility.GetAbilities();
    }
    
    // Returns a const reference to the Magical abilities map.
    const TMap<EMagicalAbilityType, FAbilityModule>& GetMagicalAbilities() const
    {
        return MagicalAbility.GetAbilities();
    }
    
    // Returns a mutable reference to the Crafting abilities map.
    TMap<ECraftingAbilityType, FAbilityModule>& GetCraftingAbilities()
    {
        return CraftingAbility.GetAbilities();
    }
    
    // Returns a const reference to the Crafting abilities map.
    const TMap<ECraftingAbilityType, FAbilityModule>& GetCraftingAbilities() const
    {
        return CraftingAbility.GetAbilities();
    }
    
    // Returns a mutable reference to the Survival abilities map.
    TMap<ESurvivalAbilityType, FAbilityModule>& GetSurvivalAbilities()
    {
        return SurvivalAbility.GetAbilities();
    }
    
    // Returns a const reference to the Survival abilities map.
    const TMap<ESurvivalAbilityType, FAbilityModule>& GetSurvivalAbilities() const
    {
        return SurvivalAbility.GetAbilities();
    }
    
    // Returns a mutable reference to the Stealth abilities map.
    TMap<EStealthAbilityType, FAbilityModule>& GetStealthAbilities()
    {
        return StealthAbility.GetAbilities();
    }
    
    // Returns a const reference to the Stealth abilities map.
    const TMap<EStealthAbilityType, FAbilityModule>& GetStealthAbilities() const
    {
        return StealthAbility.GetAbilities();
    }
    
    // Setters for replacing entire ability maps
    
    // Replaces the Martial abilities map with a new one.
    void SetMartialAbilities(const TMap<EMartialAbilityType, FAbilityModule>& NewAbilities)
    {
        MartialAbility.SetAbilities(NewAbilities);
    }
    
    // Replaces the Magical abilities map with a new one.
    void SetMagicalAbilities(const TMap<EMagicalAbilityType, FAbilityModule>& NewAbilities)
    {
        MagicalAbility.SetAbilities(NewAbilities);
    }
    
    // Replaces the Crafting abilities map with a new one.
    void SetCraftingAbilities(const TMap<ECraftingAbilityType, FAbilityModule>& NewAbilities)
    {
        CraftingAbility.SetAbilities(NewAbilities);
    }
    
    // Replaces the Survival abilities map with a new one.
    void SetSurvivalAbilities(const TMap<ESurvivalAbilityType, FAbilityModule>& NewAbilities)
    {
        SurvivalAbility.SetAbilities(NewAbilities);
    }
    
    // Replaces the Stealth abilities map with a new one.
    void SetStealthAbilities(const TMap<EStealthAbilityType, FAbilityModule>& NewAbilities)
    {
        StealthAbility.SetAbilities(NewAbilities);
    }
    
    // Template functions for ability operations
    
    // Increases the ability point of the specified ability type in the given ability data.
    template<typename AbilityData, typename AbilityType>
    void IncreaseAbilityPoint(AbilityData& Ability, AbilityType Type)
    {
        Ability.IncreaseAbilityByType(Type);
    }
    
    // Decreases the ability point of the specified ability type in the given ability data.
    template<typename AbilityData, typename AbilityType>
    void DecreaseAbilityPoint(AbilityData& Ability, AbilityType Type)
    {
        Ability.DecreaseAbilityByType(Type);
    }
    
    // Attempts to upgrade the specified ability type in the given ability data.
    template<typename AbilityData, typename AbilityType>
    void UpgradeAbility(AbilityData& Ability, AbilityType Type)
    {
        Ability.UpgradeAbilityByType(Type);
    }
    
    // Attempts to downgrade the specified ability type in the given ability data.
    template<typename AbilityData, typename AbilityType>
    void DowngradeAbility(AbilityData& Ability, AbilityType Type)
    {
        Ability.DowngradeAbilityByType(Type);
    }

};


