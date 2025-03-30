#include <memory>
#include "apcpp-glue.h"
#include "apcpp-singleplayer-config.h"

std::shared_ptr<SinglePlayerRandoConfig> sp_config = NULL;

RECOMP_DLL_FUNC(rando_sp_create_config) {
    sp_config = std::make_shared<SinglePlayerRandoConfig>();
}

// An easy get/set macro:
#define SP_GET_32(_name) \
    RECOMP_DLL_C_FUNC(rando_sp_get_##_name) { \
        RECOMP_RETURN(s32, sp_config->_name); \
    } 

#define SP_SET_32(_type, _name) \
    RECOMP_DLL_C_FUNC(rando_sp_set_##_name) { \
       sp_config->_name = RECOMP_ARG(_type, 1); \
    } 

#define SP_GET_SET_32(_type, _name) \
    SP_GET_32(_name) \
    SP_SET_32(_type, _name)

// Get/Set for enums
#define SP_GET_ENUM(_name) \
    RECOMP_DLL_C_FUNC(rando_sp_get_##_name) { \
        RECOMP_RETURN(s32, (s32)sp_config->_name); \
    } 

#define SP_SET_ENUM(_type, _name) \
    RECOMP_DLL_C_FUNC(rando_sp_set_##_name) { \
       sp_config->_name = (_type) RECOMP_ARG(s32, 1); \
    } 

#define SP_GET_SET_ENUM(_type, _name) \
    extern "C" { SP_GET_ENUM(_name) \
    SP_SET_ENUM(_type, _name) }

SP_GET_SET_ENUM(SinglePlayerRandoConfig::Accessability, accessability);
SP_GET_SET_ENUM(SinglePlayerRandoConfig::LogicDifficulty, logicDifficulty);
SP_GET_SET_32(bool, chestsMatchContents);
SP_GET_SET_32(bool, startSwordless);
SP_GET_SET_32(bool, startShieldless);
SP_GET_SET_32(bool, startWithSoaring);
SP_GET_SET_32(bool, startingHeartsAreRandom);
SP_GET_SET_32(int, startingHeartsMin);
SP_GET_SET_32(int, startingHeartsMax);
SP_GET_SET_32(int, startingHearts);
SP_GET_SET_ENUM(SinglePlayerRandoConfig::StartingHeartsAreContainersOrPieces, startingHeartsAreContainersOrPieces);
SP_GET_SET_ENUM(SinglePlayerRandoConfig::ShuffleRegionalMaps, shuffleRegionalMaps);
SP_GET_SET_ENUM(SinglePlayerRandoConfig::ShuffleBossRemains, shuffleBossRemains);
SP_GET_SET_32(bool, shuffleSpiderHouseRewards);
SP_GET_SET_ENUM(SinglePlayerRandoConfig::SkullSanity, skullSanity);
SP_GET_SET_ENUM(SinglePlayerRandoConfig::ShopSanity, shopSanity);
SP_GET_SET_32(bool, scrubSanity);
SP_GET_SET_32(bool, cowSanity);
SP_GET_SET_32(bool, shuffleCreatFairyRewards);
SP_GET_SET_32(bool, fairySanity);
SP_GET_SET_32(bool, startWithConsumables);
SP_GET_SET_32(bool, permanentChateauRomani);
SP_GET_SET_32(bool, startWithInvertedTime);
SP_GET_SET_32(bool, recieveFilledWallets);
SP_GET_SET_ENUM(SinglePlayerRandoConfig::DamageMultiplier, damageMultiplier);
SP_GET_SET_ENUM(SinglePlayerRandoConfig::DeathBehavior, deathBehavior);
