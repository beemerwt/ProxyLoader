#pragma once
#include "Exports.hpp"
#define Version_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplGetFileVersionInfoSizeA) \
    DECLARE_IMPL_NAME(ImplGetFileVersionInfoA) \
    DECLARE_IMPL_NAME(ImplGetFileVersionInfoByHandle) \
    DECLARE_IMPL_NAME(ImplGetFileVersionInfoExA) \
    DECLARE_IMPL_NAME(ImplGetFileVersionInfoExW) \
    DECLARE_IMPL_NAME(ImplGetFileVersionInfoSizeExA) \
    DECLARE_IMPL_NAME(ImplGetFileVersionInfoSizeExW) \
    DECLARE_IMPL_NAME(ImplGetFileVersionInfoSizeW) \
    DECLARE_IMPL_NAME(ImplGetFileVersionInfoW) \
    DECLARE_IMPL_NAME(ImplVerFindFileA) \
    DECLARE_IMPL_NAME(ImplVerFindFileW) \
    DECLARE_IMPL_NAME(ImplVerInstallFileA) \
    DECLARE_IMPL_NAME(ImplVerInstallFileW) \
    DECLARE_IMPL_NAME(ImplVerLanguageNameA) \
    DECLARE_IMPL_NAME(ImplVerLanguageNameW) \
    DECLARE_IMPL_NAME(ImplVerQueryValueA) \
    DECLARE_IMPL_NAME(ImplVerQueryValueW) \

namespace VersionExports {
    constexpr std::array<std::string_view, 17> GetAllImplNames() {
        return { Version_IMPL_FUNCTION_LIST };
    }
}