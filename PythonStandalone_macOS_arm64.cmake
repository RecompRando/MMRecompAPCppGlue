cmake_minimum_required(VERSION 3.20)
project(UsePythonStandalone)

include(FetchContent)

set(PYTHON_URL "https://github.com/astral-sh/python-build-standalone/releases/download/20250409/cpython-3.11.12+20250409-aarch64-apple-darwin-install_only_stripped.tar.gz")
set(PYTHON_ARCHIVE "${CMAKE_BINARY_DIR}/cpython.tar.gz")
set(PYTHON_EXTRACT_DIR "${CMAKE_BINARY_DIR}/python-standalone")

if(NOT EXISTS "${PYTHON_ARCHIVE}")
    message(STATUS "Downloading Python artifact...")
    file(DOWNLOAD "${PYTHON_URL}" "${PYTHON_ARCHIVE}" SHOW_PROGRESS)
endif()

if(NOT EXISTS "${PYTHON_EXTRACT_DIR}")
    message(STATUS "Extracting Python artifact...")
    file(MAKE_DIRECTORY "${PYTHON_EXTRACT_DIR}")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xzf "${PYTHON_ARCHIVE}"
        WORKING_DIRECTORY "${PYTHON_EXTRACT_DIR}"
    )
endif()

file(GLOB EXTRACTED_DIRS LIST_DIRECTORIES true "${PYTHON_EXTRACT_DIR}/*")
list(GET EXTRACTED_DIRS 0 PYTHON_ROOT)

add_library(python_standalone INTERFACE)
target_include_directories(python_standalone INTERFACE "${PYTHON_ROOT}/include/python3.11")
target_link_directories(python_standalone INTERFACE "${PYTHON_ROOT}/lib")
target_link_libraries(python_standalone INTERFACE "${PYTHON_ROOT}/lib/libpython3.11.dylib")

function(link_python_standalone TARGET_NAME)
    target_link_libraries(${TARGET_NAME} PRIVATE python_standalone)
    # Copy the interpreter next to the target so it ships with the mod.
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PYTHON_ROOT}/lib/libpython3.11.dylib"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>/libpython3.11.dylib"
    )
    # The python-build-standalone dylib has install_name /install/lib/libpython3.11.dylib,
    # which gets baked into the target as an absolute dependency that won't exist on the
    # user's machine. Rewrite it to @loader_path so dyld finds the copy placed alongside.
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND install_name_tool -change
            "/install/lib/libpython3.11.dylib"
            "@loader_path/libpython3.11.dylib"
            "$<TARGET_FILE:${TARGET_NAME}>"
    )
endfunction()

set(PYTHON_EXE "${PYTHON_ROOT}/bin/python3.11" CACHE PATH "Python executable")
set(PYTHON_STANDALONE_ROOT "${PYTHON_ROOT}" CACHE PATH "Root of extracted Python standalone distribution")
