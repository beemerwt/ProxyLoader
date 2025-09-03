#pragma once
#include "Exports.hpp"
#define DInput8_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplDirectInput8Create) \

namespace DInput8Exports {
    constexpr std::array<std::string_view, 1> GetAllImplNames() {
        return { DInput8_IMPL_FUNCTION_LIST };
    }
}
