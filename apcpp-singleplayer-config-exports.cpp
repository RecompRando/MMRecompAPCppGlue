#include <memory>
#include "apcpp-glue.h"
#include "apcpp-singleplayer-config.h"


// extern "C" {
    RECOMP_DLL_FUNC(rando_save_run_yaml) {
        u32 slot = RECOMP_ARG(u32, 1);
        std::string yaml_text = RECOMP_ARG_STR(2);
    }
// };