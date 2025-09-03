#pragma once
#include "Exports.hpp"
#define DInput_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplDirectInputCreateA) \
    DECLARE_IMPL_NAME(ImplDirectInputCreateEx) \
    DECLARE_IMPL_NAME(ImplDirectInputCreateW) \

namespace DInputExports {
    constexpr std::array<std::string_view, 3> GetAllImplNames() {
        return { DInput_IMPL_FUNCTION_LIST };
    }
}
