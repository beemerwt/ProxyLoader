#pragma once
#include "Exports.hpp"

#define Shared_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplDllCanUnloadNow) \
    DECLARE_IMPL_NAME(ImplDllGetClassObject) \
    DECLARE_IMPL_NAME(ImplDllRegisterServer) \
    DECLARE_IMPL_NAME(ImplDllUnregisterServer) \
    DECLARE_IMPL_NAME(ImplPrivate1) \
    DECLARE_IMPL_NAME(ImplDebugSetMute) \
    DECLARE_IMPL_NAME(ImplDebugSetLevel) \
    DECLARE_IMPL_NAME(ImplGetDeviceID) \

namespace SharedExports {
    inline static constexpr size_t arysize = 8;
    constexpr std::array<std::string_view, arysize> GetAllImplNames() {
        return { Shared_IMPL_FUNCTION_LIST };
    }
}