#pragma once
#include "Exports.hpp"
#define D3D10_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplD3D10CompileEffectFromMemory) \
    DECLARE_IMPL_NAME(ImplD3D10CompileShader) \
    DECLARE_IMPL_NAME(ImplD3D10CreateBlob) \
    DECLARE_IMPL_NAME(ImplD3D10CreateDevice) \
    DECLARE_IMPL_NAME(ImplD3D10CreateDeviceAndSwapChain) \
    DECLARE_IMPL_NAME(ImplD3D10CreateEffectFromMemory) \
    DECLARE_IMPL_NAME(ImplD3D10CreateEffectPoolFromMemory) \
    DECLARE_IMPL_NAME(ImplD3D10CreateStateBlock) \
    DECLARE_IMPL_NAME(ImplD3D10DisassembleEffect) \
    DECLARE_IMPL_NAME(ImplD3D10DisassembleShader) \
    DECLARE_IMPL_NAME(ImplD3D10GetGeometryShaderProfile) \
    DECLARE_IMPL_NAME(ImplD3D10GetInputAndOutputSignatureBlob) \
    DECLARE_IMPL_NAME(ImplD3D10GetInputSignatureBlob) \
    DECLARE_IMPL_NAME(ImplD3D10GetOutputSignatureBlob) \
    DECLARE_IMPL_NAME(ImplD3D10GetPixelShaderProfile) \
    DECLARE_IMPL_NAME(ImplD3D10GetShaderDebugInfo) \
    DECLARE_IMPL_NAME(ImplD3D10GetVersion) \
    DECLARE_IMPL_NAME(ImplD3D10GetVertexShaderProfile) \
    DECLARE_IMPL_NAME(ImplD3D10PreprocessShader) \
    DECLARE_IMPL_NAME(ImplD3D10ReflectShader) \
    DECLARE_IMPL_NAME(ImplD3D10RegisterLayers) \
    DECLARE_IMPL_NAME(ImplD3D10StateBlockMaskDifference) \
    DECLARE_IMPL_NAME(ImplD3D10StateBlockMaskDisableAll) \
    DECLARE_IMPL_NAME(ImplD3D10StateBlockMaskDisableCapture) \
    DECLARE_IMPL_NAME(ImplD3D10StateBlockMaskEnableAll) \
    DECLARE_IMPL_NAME(ImplD3D10StateBlockMaskEnableCapture) \
    DECLARE_IMPL_NAME(ImplD3D10StateBlockMaskGetSetting) \
    DECLARE_IMPL_NAME(ImplD3D10StateBlockMaskIntersect) \
    DECLARE_IMPL_NAME(ImplD3D10StateBlockMaskUnion) \

namespace D3D10Exports {
    inline constexpr static std::array<std::string_view, 29> GetAllImplNames() {
        return { D3D10_IMPL_FUNCTION_LIST };
    }
}