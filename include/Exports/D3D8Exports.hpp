#pragma once
#include "Exports.hpp"

#define D3D8_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplDirect3DCreate8) \
    DECLARE_IMPL_NAME(ImplDirect3D8EnableMaximizedWindowedModeShim) \
    DECLARE_IMPL_NAME(ImplValidatePixelShader) \
    DECLARE_IMPL_NAME(ImplValidateVertexShader) \

struct D3D8Exports {
    inline static constexpr size_t arysize = 4;
    inline static constexpr std::array<std::string_view, arysize> GetAllImplNames() {
        return { D3D8_IMPL_FUNCTION_LIST };
    }
};