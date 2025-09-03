#pragma once
#include "Exports.hpp"
#define MSACM32_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplacmDriverAddA) \
    DECLARE_IMPL_NAME(ImplacmDriverAddW) \
    DECLARE_IMPL_NAME(ImplacmDriverClose) \
    DECLARE_IMPL_NAME(ImplacmDriverDetailsA) \
    DECLARE_IMPL_NAME(ImplacmDriverDetailsW) \
    DECLARE_IMPL_NAME(ImplacmDriverEnum) \
    DECLARE_IMPL_NAME(ImplacmDriverID) \
    DECLARE_IMPL_NAME(ImplacmDriverMessage) \
    DECLARE_IMPL_NAME(ImplacmDriverOpen) \
    DECLARE_IMPL_NAME(ImplacmDriverPriority) \
    DECLARE_IMPL_NAME(ImplacmDriverRemove) \
    DECLARE_IMPL_NAME(ImplacmFilterChooseA) \
    DECLARE_IMPL_NAME(ImplacmFilterChooseW) \
    DECLARE_IMPL_NAME(ImplacmFilterDetailsA) \
    DECLARE_IMPL_NAME(ImplacmFilterDetailsW) \
    DECLARE_IMPL_NAME(ImplacmFilterEnumA) \
    DECLARE_IMPL_NAME(ImplacmFilterEnumW) \
    DECLARE_IMPL_NAME(ImplacmFilterTagDetailsA) \
    DECLARE_IMPL_NAME(ImplacmFilterTagDetailsW) \
    DECLARE_IMPL_NAME(ImplacmFilterTagEnumA) \
    DECLARE_IMPL_NAME(ImplacmFilterTagEnumW) \
    DECLARE_IMPL_NAME(ImplacmFormatChooseA) \
    DECLARE_IMPL_NAME(ImplacmFormatChooseW) \
    DECLARE_IMPL_NAME(ImplacmFormatDetailsA) \
    DECLARE_IMPL_NAME(ImplacmFormatDetailsW) \
    DECLARE_IMPL_NAME(ImplacmFormatEnumA) \
    DECLARE_IMPL_NAME(ImplacmFormatEnumW) \
    DECLARE_IMPL_NAME(ImplacmFormatSuggest) \
    DECLARE_IMPL_NAME(ImplacmFormatTagDetailsA) \
    DECLARE_IMPL_NAME(ImplacmFormatTagDetailsW) \
    DECLARE_IMPL_NAME(ImplacmFormatTagEnumA) \
    DECLARE_IMPL_NAME(ImplacmFormatTagEnumW) \
    DECLARE_IMPL_NAME(ImplacmGetVersion) \
    DECLARE_IMPL_NAME(ImplacmMetrics) \
    DECLARE_IMPL_NAME(ImplacmStreamClose) \
    DECLARE_IMPL_NAME(ImplacmStreamConvert) \
    DECLARE_IMPL_NAME(ImplacmStreamMessage) \
    DECLARE_IMPL_NAME(ImplacmStreamOpen) \
    DECLARE_IMPL_NAME(ImplacmStreamPrepareHeader) \
    DECLARE_IMPL_NAME(ImplacmStreamReset) \
    DECLARE_IMPL_NAME(ImplacmStreamSize) \
    DECLARE_IMPL_NAME(ImplacmStreamUnprepareHeader) \

namespace MSACM32Exports {
    constexpr std::array<std::string_view, 42> GetAllImplNames() {
        return { MSACM32_IMPL_FUNCTION_LIST };
    }
}
