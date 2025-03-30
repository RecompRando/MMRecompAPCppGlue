#pragma once

#include <string>
#include <filesystem>
#include "Archipelago.h"


class SinglePlayerRandoConfig {
public:
    SinglePlayerRandoConfig();
    ~SinglePlayerRandoConfig();

    bool write_to_file(std::filesystem::path out_file);

    enum class Accessability {
        FULL = 0,
        MINIMAL = 1,
    };
    Accessability accessability = Accessability::FULL;

    enum class LogicDifficulty {
        EASY = 0,
        NORMAL = 1,
        NO_LOGIC = 2
    };
    LogicDifficulty logicDifficulty = LogicDifficulty::NORMAL;

    bool chestsMatchContents = true;
    bool startSwordless = false;
    bool startShieldless = false;
    bool startWithSoaring = true;

    bool startingHeartsAreRandom = false;
    int startingHeartsMin = 4;
    int startingHeartsMax = 12;
    int startingHearts = 12;
    
    enum class StartingHeartsAreContainersOrPieces {
        CONTAINERS = 0,
        PIECES = 1
    };
    StartingHeartsAreContainersOrPieces startingHeartsAreContainersOrPieces = StartingHeartsAreContainersOrPieces::CONTAINERS;

    enum class ShuffleRegionalMaps {
        VANILLA = 0,
        STARTING = 1,
        ANYWHERE = 2
    };
    ShuffleRegionalMaps shuffleRegionalMaps = ShuffleRegionalMaps::VANILLA;

    enum class ShuffleBossRemains {
        VANILLA = 0,
        ANYWHERE = 1,
        BOSSES = 2
    };
    ShuffleBossRemains shuffleBossRemains = ShuffleBossRemains::VANILLA;

    bool shuffleSpiderHouseRewards = false;

    enum class SkullSanity {
        VANILLA = 0,
        ANYTHING = 1,
        IGNORE = 2
    };
    SkullSanity skullSanity = SkullSanity::VANILLA;

    enum class ShopSanity {
        VANILLA = 0,
        ENABLED = 1,
        ADVANCED = 2
    };
    ShopSanity shopSanity = ShopSanity::VANILLA;

    bool scrubSanity = false;
    bool cowSanity = false;
    bool shuffleCreatFairyRewards = false;
    bool fairySanity = false;
    bool startWithConsumables = false;
    bool permanentChateauRomani = true;
    bool startWithInvertedTime = true;
    bool recieveFilledWallets = true;
    
    enum class DamageMultiplier {
        HALF = 0,
        NORMAL = 1,
        DOUBLE = 2,
        QUAD = 3,
        ONE_HOT_KO = 4
    };
    DamageMultiplier damageMultiplier = DamageMultiplier::NORMAL;

    enum class DeathBehavior {
        VANILLA = 0,
        FAST = 1,
        MOON_CRASH = 2
    };
    DeathBehavior deathBehavior = DeathBehavior::VANILLA;
};

