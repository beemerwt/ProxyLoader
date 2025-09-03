cmake_minimum_required(VERSION 3.10)
project(ProxyLoader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output target_include_directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES
    "${SRC_DIR}/*.c"
    "${SRC_DIR}/*.cpp"
)

add_library(ProxyLoader SHARED ${SOURCES})

set(DEF_FILE "${CMAKE_SOURCE_DIR}/version.def")
target_sources(ProxyLoader PRIVATE "${DEF_FILE}")

target_include_directories(ProxyLoader
    PRIVATE
        "${SRC_DIR}"
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/include/Exports"
)

# Add MinHook
add_subdirectory(libs/minhook-master)
target_link_libraries(ProxyLoader PRIVATE minhook)
target_include_directories(ProxyLoader PRIVATE
    "${CMAKE_SOURCE_DIR}/libs/minhook-master/include"
)

if (MINGW)
  set_target_properties(ProxyLoader PROPERTIES IMPORT_PREFIX "")
endif()

set_target_properties(ProxyLoader PROPERTIES
  OUTPUT_NAME "version"            # base name for all artifacts
  RUNTIME_OUTPUT_NAME "version"    # DLL file name
  ARCHIVE_OUTPUT_NAME "version"    # import library name
  PREFIX ""
)