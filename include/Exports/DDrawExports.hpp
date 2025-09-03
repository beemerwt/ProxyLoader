#pragma once
#include "Exports.hpp"
#define DDraw_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplAcquireDDThreadLock) \
    DECLARE_IMPL_NAME(ImplCompleteCreateSysmemSurface) \
    DECLARE_IMPL_NAME(ImplD3DParseUnknownCommand) \
    DECLARE_IMPL_NAME(ImplDDGetAttachedSurfaceLcl) \
    DECLARE_IMPL_NAME(ImplDDInternalLock) \
    DECLARE_IMPL_NAME(ImplDDInternalUnlock) \
    DECLARE_IMPL_NAME(ImplDSoundHelp) \
    DECLARE_IMPL_NAME(ImplDirectDrawCreate) \
    DECLARE_IMPL_NAME(ImplDirectDrawCreateClipper) \
    DECLARE_IMPL_NAME(ImplDirectDrawCreateEx) \
    DECLARE_IMPL_NAME(ImplDirectDrawEnumerateA) \
    DECLARE_IMPL_NAME(ImplDirectDrawEnumerateExA) \
    DECLARE_IMPL_NAME(ImplDirectDrawEnumerateExW) \
    DECLARE_IMPL_NAME(ImplDirectDrawEnumerateW) \
    DECLARE_IMPL_NAME(ImplGetDDSurfaceLocal) \
    DECLARE_IMPL_NAME(ImplGetOLEThunkData) \
    DECLARE_IMPL_NAME(ImplGetSurfaceFromDC) \
    DECLARE_IMPL_NAME(ImplRegisterSpecialCase) \
    DECLARE_IMPL_NAME(ImplReleaseDDThreadLock) \
    DECLARE_IMPL_NAME(ImplSetAppCompatData) \

namespace DDrawExports {
    constexpr std::array<std::string_view, 20> GetAllImplNames() {
        return { DDraw_IMPL_FUNCTION_LIST };
    }
}
