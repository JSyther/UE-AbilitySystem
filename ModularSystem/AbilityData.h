// This is example modular ability system for educational purposes.

USTRUCT(BlueprintType)
struct FAbilityModule
{
    GENERATED_BODY()

public:
    // Whether the ability is unlocked or not
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
    bool bUnlocked = false;

    // Number of active points currently used on this ability
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability", meta = (ClampMin = "0"))
    int8 Point = 0;

    // Maximum points this ability can have
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability", meta = (ClampMin = "1"))
    int8 MaxPoint = 5;

    // Points allocated from character's pool
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability", meta = (ClampMin = "0"))
    int8 AllocatedPoint = 0;

public:
    void Reset()
    {
        bUnlocked = false;
        Point = 0;
        AllocatedPoint = 0;
        MaxPoint = 5;
    }

    void IncreasePoint()
    {
        if (Point < MaxPoint && Point < AllocatedPoint)
        {
            ++Point;
            UpdateUnlockStatus();
        }
    }

    void DecreasePoint()
    {
        if (Point > 0)
        {
            --Point;
            UpdateUnlockStatus();
        }
    }

private:
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
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    TMap<EMagicalAbilityType, FAbilityModule> MagicalAbilities;

public:
    FMagicalAbility()
    {
        for (uint8 i = static_cast<uint8>(EMagicalAbilityType::Null) + 1; i < static_cast<uint8>(EMagicalAbilityType::Max); ++i)
        {
            MagicalAbilities.Add(static_cast<EMagicalAbilityType>(i), FAbilityModule());
        }
    }

    bool operator==(const FMagicalAbility& Other) const
    {
        return AreMapsEqual(MagicalAbilities, Other.MagicalAbilities);
    }

    bool operator!=(const FMagicalAbility& Other) const
    {
        return !(*this == Other);
    }

    TMap<EMagicalAbilityType, FAbilityModule>& GetAbilities()
    {
        return MagicalAbilities;
    }

    const TMap<EMagicalAbilityType, FAbilityModule>& GetAbilities() const
    {
        return MagicalAbilities;
    }

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

    void ResetAbilityByType(EMagicalAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            MagicalAbilities[Type].Reset();
        }
    }

    void IncreaseAbilityByType(EMagicalAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            MagicalAbilities[Type].IncreasePoint();
        }
    }

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
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    TMap<ECraftingAbilityType, FAbilityModule> CraftingAbilities;

public:
    FCraftingAbility()
    {
        for (uint8 i = static_cast<uint8>(ECraftingAbilityType::Null) + 1; i < static_cast<uint8>(ECraftingAbilityType::Max); ++i)
        {
            CraftingAbilities.Add(static_cast<ECraftingAbilityType>(i), FAbilityModule());
        }
    }

    bool operator==(const FCraftingAbility& Other) const
    {
        return AreMapsEqual(CraftingAbilities, Other.CraftingAbilities);
    }

    bool operator!=(const FCraftingAbility& Other) const
    {
        return !(*this == Other);
    }

    TMap<ECraftingAbilityType, FAbilityModule>& GetAbilities()
    {
        return CraftingAbilities;
    }

    const TMap<ECraftingAbilityType, FAbilityModule>& GetAbilities() const
    {
        return CraftingAbilities;
    }

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

    void ResetAbilityByType(ECraftingAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            CraftingAbilities[Type].Reset();
        }
    }

    void IncreaseAbilityByType(ECraftingAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            CraftingAbilities[Type].IncreasePoint();
        }
    }

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
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    TMap<ESurvivalAbilityType, FAbilityModule> SurvivalAbilities;

public:
    FSurvivalAbility()
    {
        for (uint8 i = static_cast<uint8>(ESurvivalAbilityType::Null) + 1; i < static_cast<uint8>(ESurvivalAbilityType::Max); ++i)
        {
            SurvivalAbilities.Add(static_cast<ESurvivalAbilityType>(i), FAbilityModule());
        }
    }

    bool operator==(const FSurvivalAbility& Other) const
    {
        return AreMapsEqual(SurvivalAbilities, Other.SurvivalAbilities);
    }

    bool operator!=(const FSurvivalAbility& Other) const
    {
        return !(*this == Other);
    }

    TMap<ESurvivalAbilityType, FAbilityModule>& GetAbilities()
    {
        return SurvivalAbilities;
    }

    const TMap<ESurvivalAbilityType, FAbilityModule>& GetAbilities() const
    {
        return SurvivalAbilities;
    }

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

    void ResetAbilityByType(ESurvivalAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            SurvivalAbilities[Type].Reset();
        }
    }

    void IncreaseAbilityByType(ESurvivalAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            SurvivalAbilities[Type].IncreasePoint();
        }
    }

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
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    TMap<EStealthAbilityType, FAbilityModule> StealthAbilities;

public:
    FStealthAbility()
    {
        for (uint8 i = static_cast<uint8>(EStealthAbilityType::Null) + 1; i < static_cast<uint8>(EStealthAbilityType::Max); ++i)
        {
            StealthAbilities.Add(static_cast<EStealthAbilityType>(i), FAbilityModule());
        }
    }

    bool operator==(const FStealthAbility& Other) const
    {
        return AreMapsEqual(StealthAbilities, Other.StealthAbilities);
    }

    bool operator!=(const FStealthAbility& Other) const
    {
        return !(*this == Other);
    }

    TMap<EStealthAbilityType, FAbilityModule>& GetAbilities()
    {
        return StealthAbilities;
    }

    const TMap<EStealthAbilityType, FAbilityModule>& GetAbilities() const
    {
        return StealthAbilities;
    }

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

    void ResetAbilityByType(EStealthAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            StealthAbilities[Type].Reset();
        }
    }

    void IncreaseAbilityByType(EStealthAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            StealthAbilities[Type].IncreasePoint();
        }
    }

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

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    FMartialAbility MartialAbility;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    FMagicalAbility MagicalAbility;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    FCraftingAbility CraftingAbility;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    FSurvivalAbility SurvivalAbility;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
    FStealthAbility StealthAbility;

    // Summary fields
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability Summary")
    int32 AbilityPoints = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability Summary")
    int32 MaxAbilityPoints = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability Summary")
    int32 AllocatedPoints = 0;

public:
    // Equality operators
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

    bool operator!=(const FAbility& Other) const
    {
        return !(*this == Other);
    }

    // Getters for summary fields
    int32 GetAbilityPoints() const { return AbilityPoints; }
    int32 GetMaxAbilityPoints() const { return MaxAbilityPoints; }
    int32 GetAllocatedPoints() const { return AllocatedPoints; }

    // Setters for summary fields
    void SetAbilityPoints(int32 NewPoints) { AbilityPoints = NewPoints; }
    void SetMaxAbilityPoints(int32 NewMaxPoints) { MaxAbilityPoints = NewMaxPoints; }
    void SetAllocatedPoints(int32 NewAllocatedPoints) { AllocatedPoints = NewAllocatedPoints; }

    // Getters for ability maps inside structs
    TMap<EMartialAbilityType, FAbilityModule>& GetMartialAbilities()
    {
        return MartialAbility.GetAbilities();
    }

    const TMap<EMartialAbilityType, FAbilityModule>& GetMartialAbilities() const
    {
        return MartialAbility.GetAbilities();
    }

    TMap<EMagicalAbilityType, FAbilityModule>& GetMagicalAbilities()
    {
        return MagicalAbility.GetAbilities();
    }

    const TMap<EMagicalAbilityType, FAbilityModule>& GetMagicalAbilities() const
    {
        return MagicalAbility.GetAbilities();
    }

    TMap<ECraftingAbilityType, FAbilityModule>& GetCraftingAbilities()
    {
        return CraftingAbility.GetAbilities();
    }

    const TMap<ECraftingAbilityType, FAbilityModule>& GetCraftingAbilities() const
    {
        return CraftingAbility.GetAbilities();
    }

    TMap<ESurvivalAbilityType, FAbilityModule>& GetSurvivalAbilities()
    {
        return SurvivalAbility.GetAbilities();
    }

    const TMap<ESurvivalAbilityType, FAbilityModule>& GetSurvivalAbilities() const
    {
        return SurvivalAbility.GetAbilities();
    }

    TMap<EStealthAbilityType, FAbilityModule>& GetStealthAbilities()
    {
        return StealthAbility.GetAbilities();
    }

    const TMap<EStealthAbilityType, FAbilityModule>& GetStealthAbilities() const
    {
        return StealthAbility.GetAbilities();
    }

    // You can add setters if you want to replace whole maps, similar to:
    void SetMartialAbilities(const TMap<EMartialAbilityType, FAbilityModule>& NewAbilities)
    {
        MartialAbility.SetAbilities(NewAbilities);
    }
    
    void SetMagicalAbilities(const TMap<EMagicalAbilityType, FAbilityModule>& NewAbilities)
    {
        MagicalAbility.SetAbilities(NewAbilities);
    }
    
    void SetCraftingAbilities(const TMap<ECraftingAbilityType, FAbilityModule>& NewAbilities)
    {
        CraftingAbility.SetAbilities(NewAbilities);
    }
    
    void SetSurvivalAbilities(const TMap<ESurvivalAbilityType, FAbilityModule>& NewAbilities)
    {
        SurvivalAbility.SetAbilities(NewAbilities);
    }
    
    void SetStealthAbilities(const TMap<EStealthAbilityType, FAbilityModule>& NewAbilities)
    {
        StealthAbility.SetAbilities(NewAbilities);
    }


    template<typename AbilityData, typename AbilityType>
    void IncreaseAbilityPoint(AbilityData& Ability, AbilityType Type)
    {
        Ability.IncreaseAbilityByType(Type);
    }

    template<typename AbilityData, typename AbilityType>
    void DecreaseAbilityPoint(AbilityData& Ability, AbilityType Type)
    {
        Ability.DecreaseAbilityByType(Type);
    }

    template<typename AbilityData, typename AbilityType>
    void UpgradeAbility(AbilityData& Ability, AbilityType Type)
    {
        Ability.UpgradeAbilityByType(Type);
    }

    template<typename AbilityData, typename AbilityType>
    void DowngradeAbility(AbilityData& Ability, AbilityType Type)
    {
        Ability.DowngradeAbilityByType(Type);
    }
};


