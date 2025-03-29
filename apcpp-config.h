#include <string>


class SinglePlayerRandoConfig {
public:
    SinglePlayerRandoConfig();
    ~SinglePlayerRandoConfig();

    enum class Accessability {
        FULL,
        MINIMAL,
    };
    Accessability accessability = Accessability::FULL;

    enum class LogicDifficulty {
        EASY,
        NORMAL,
        NO_LOGIC
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
        CONTAINERS,
        PIECES
    };
    StartingHeartsAreContainersOrPieces startingHeartsAreContainersOrPieces = StartingHeartsAreContainersOrPieces::CONTAINERS;

    enum class ShuffleRegionalMaps {
        VANILLA,
        STARTING,
        ANYWHERE
    };
    ShuffleRegionalMaps shuffleRegionalMaps = ShuffleRegionalMaps::VANILLA;

    enum class ShuffleBossRemains {
        VANILLA,
        ANYWHERE,
        BOSSES
    };

    bool shuffleSpiderHouseRewards = false;

    enum class SkullSanity {
        VANILLA,
        ANYTHING,
        IGNORE
    };
    SkullSanity skullSanity = SkullSanity::VANILLA;

    enum class ShopSanity {
        VANILLA,
        ENABLED,
        ADVANCED
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
        HALF,
        NORMAL,
        DOUBLE,
        QUAD,
        ONE_HOT_KO
    };
    DamageMultiplier damageMultiplier = DamageMultiplier::NORMAL;

    enum class DeathBehavior {
        VANILLA,
        FAST,
        MOON_CRASH
    };
    DeathBehavior deathBehavior = DeathBehavior::VANILLA;
};