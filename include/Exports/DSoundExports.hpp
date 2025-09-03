#pragma once
#include "Exports.hpp"
#define DSound_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplDirectSoundCaptureCreate) \
    DECLARE_IMPL_NAME(ImplDirectSoundCaptureCreate8) \
    DECLARE_IMPL_NAME(ImplDirectSoundCaptureEnumerateA) \
    DECLARE_IMPL_NAME(ImplDirectSoundCaptureEnumerateW) \
    DECLARE_IMPL_NAME(ImplDirectSoundCreate) \
    DECLARE_IMPL_NAME(ImplDirectSoundCreate8) \
    DECLARE_IMPL_NAME(ImplDirectSoundEnumerateA) \
    DECLARE_IMPL_NAME(ImplDirectSoundEnumerateW) \
    DECLARE_IMPL_NAME(ImplDirectSoundFullDuplexCreate) \

namespace DSoundExports {
    constexpr std::array<std::string_view, 9> GetAllImplNames() {
        return { DSound_IMPL_FUNCTION_LIST };
    }
}