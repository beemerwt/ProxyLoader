#pragma once
#include "Exports.hpp"
#define D3D9_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplD3DPERF_BeginEvent) \
    DECLARE_IMPL_NAME(ImplD3DPERF_EndEvent) \
    DECLARE_IMPL_NAME(ImplD3DPERF_GetStatus) \
    DECLARE_IMPL_NAME(ImplD3DPERF_QueryRepeatFrame) \
    DECLARE_IMPL_NAME(ImplD3DPERF_SetMarker) \
    DECLARE_IMPL_NAME(ImplD3DPERF_SetOptions) \
    DECLARE_IMPL_NAME(ImplD3DPERF_SetRegion) \
    DECLARE_IMPL_NAME(ImplDirect3D9EnableMaximizedWindowedModeShim) \
    DECLARE_IMPL_NAME(ImplDirect3DCreate9) \
    DECLARE_IMPL_NAME(ImplDirect3DCreate9Ex) \
    DECLARE_IMPL_NAME(ImplDirect3DCreate9On12) \
    DECLARE_IMPL_NAME(ImplDirect3DCreate9On12Ex) \
    DECLARE_IMPL_NAME(ImplDirect3DShaderValidatorCreate9) \
    DECLARE_IMPL_NAME(ImplPSGPError) \
    DECLARE_IMPL_NAME(ImplPSGPSampleTexture) \

namespace D3D9Exports {
    constexpr std::array<std::string_view, 15> GetAllImplNames() {
        return { D3D9_IMPL_FUNCTION_LIST };
    }
}