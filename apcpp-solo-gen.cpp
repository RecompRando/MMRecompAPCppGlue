#include <cstdio>

#include "apcpp-solo-gen.h"

// _DEBUG causes Python to link the debug binary, which isn't present in normal installs.
#undef _DEBUG
#include <Python.h>

// Converts a path to a UTF-8 encoded std::string by going through a std::u8string.
std::string path_to_string_utf8(const std::filesystem::path& path) {
    std::u8string path_u8string = path.u8string();
    std::string to_escape{ reinterpret_cast<const char*>(path_u8string.c_str()), path_u8string.size() };

    std::string ret{};
    ret.reserve(to_escape.size());
    for (char c : to_escape) {
        // Escape backslashes
        if (c == '\\') {
            ret += '\\';
        }
        ret += c;
    }
    return ret;
}

bool sologen::generate(const std::filesystem::path& yaml_dir, const std::filesystem::path& output_dir) {
    PyStatus status;
    
    PyPreConfig preconfig;
    PyPreConfig_InitPythonConfig(&preconfig);
    Py_PreInitialize(&preconfig);

    PyConfig config;
    PyConfig_InitPythonConfig(&config);  // Use isolated config if you don't want to inherit env

    PyConfig_SetBytesString(&config, &config.program_name, "minipelago");
    
    wchar_t* zip_path = nullptr;
    status = PyConfig_SetBytesString(&config, &zip_path, path_to_string_utf8(output_dir / "python311.zip").c_str());
    // status = PyConfig_SetBytesString(&config, &zip_path, "C:/n64/MMRecompRandoMinipelago/build/minipelago/minipelago.zip");
    // status = PyConfig_SetBytesString(&config, &zip_path, "C:\\\\Users\\\\aaron\\\\AppData\\\\Local\\\\Zelda64Recompiled\\\\saves\\\\mm_recomp_rando\\\\python311.zip");

    config.module_search_paths_set = 1;
    PyWideStringList_Append(&config.module_search_paths, zip_path);
    PyMem_RawFree(zip_path);

    Py_InitializeFromConfig(&config);
    PyRun_SimpleString("import sys");

    // remove last path entry and add the zip file based on the current dynamic library path
    PyRun_SimpleString("sys.path.pop()");
    auto mod_zip_path = std::string("sys.path.insert(0, '") + path_to_string_utf8(output_dir / "minipelago.zip") + "')";
    PyRun_SimpleString(mod_zip_path.c_str());

    // debug print sys.path
    PyRun_SimpleString("print(sys.path)");

    // Create a Python list to simulate sys.argv
    std::vector<std::string> args = {
        "MMGenerate.py",  // argv[0] is typically the script name
        "--player_files_path", path_to_string_utf8(yaml_dir),
        "--outputpath", path_to_string_utf8(output_dir)
    };
  
    PyObject* py_argv = PyList_New(args.size());
    for (size_t i = 0; i < args.size(); ++i) {
        PyList_SetItem(py_argv, i, PyUnicode_FromString(args[i].c_str()));
    }

    // Set sys.argv
    PySys_SetObject("argv", py_argv);

    PyObject* globals = PyDict_New();
    PyObject* locals = PyDict_New();
    PyObject* result = PyRun_String(
        "from MMGenerate import main as generate\n"
        "generate()",
        Py_file_input, globals, locals
    );

    bool success;
    if (result) {
        success = true;
        Py_DECREF(result);
    }
    else {
        success = false;
        // Exception occurred
        if (PyErr_Occurred()) {
            PyErr_Print();  // Print to stderr
        }
    }

    Py_DECREF(globals);
    Py_DECREF(locals);

    Py_DECREF(py_argv);

    // finalize python
    Py_Finalize();

    return success;
}
