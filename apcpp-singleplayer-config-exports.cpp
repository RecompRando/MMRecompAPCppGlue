#include <memory>
#include <filesystem>
#include <string>
#include <format>
#include <fstream>
#include <iostream>

#include "apcpp-glue.h"
#include "apcpp-singleplayer-config.h"

namespace fs = std::filesystem;
RECOMP_DLL_FUNC(rando_save_run_yaml) {
    std::u8string savepath_str = RECOMP_ARG_U8STR(0);
    // std::u8string savepath_str = u8"testing 1 2 3\n";
    u32 slot = RECOMP_ARG(u32, 1);
    std::string yaml_text = RECOMP_ARG_STR(2);

    std::cout << yaml_text;

    fs::path savefile(savepath_str);
    fs::path yamlfile = fs::path(savefile).parent_path().append(std::format("RANDO_SLOT_{}.yaml", slot));

    std::ofstream out(yamlfile);
    try {
        out << yaml_text;
    } catch (std::exception e){
        std::cout << e.what();
    }
    out.close();
}

RECOMP_DLL_FUNC(rando_append_run_yaml) {
    std::u8string savepath_str = RECOMP_ARG_U8STR(0);
    // std::u8string savepath_str = u8"testing 1 2 3\n";
    u32 slot = RECOMP_ARG(u32, 1);
    std::string yaml_text = RECOMP_ARG_STR(2);

    std::cout << yaml_text;

    fs::path savefile(savepath_str);
    fs::path yamlfile = fs::path(savefile).parent_path().append(std::format("RANDO_SLOT_{}.yaml", slot));

    std::ofstream out = std::ofstream(yamlfile, std::ios::app);
    try {
        out << yaml_text;
    } catch (std::exception e){
        std::cout << e.what();
    }
    out.close();
}
