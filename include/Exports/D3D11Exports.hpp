#pragma once
#include "Exports.hpp"
#define D3D11_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplCreateDirect3D11DeviceFromDXGIDevice) \
    DECLARE_IMPL_NAME(ImplCreateDirect3D11SurfaceFromDXGISurface) \
    DECLARE_IMPL_NAME(ImplD3D11CoreCreateDevice) \
    DECLARE_IMPL_NAME(ImplD3D11CoreCreateLayeredDevice) \
    DECLARE_IMPL_NAME(ImplD3D11CoreGetLayeredDeviceSize) \
    DECLARE_IMPL_NAME(ImplD3D11CoreRegisterLayers) \
    DECLARE_IMPL_NAME(ImplD3D11CreateDevice) \
    DECLARE_IMPL_NAME(ImplD3D11CreateDeviceAndSwapChain) \
    DECLARE_IMPL_NAME(ImplD3D11CreateDeviceForD3D12) \
    DECLARE_IMPL_NAME(ImplD3D11On12CreateDevice) \
    DECLARE_IMPL_NAME(ImplD3DKMTCloseAdapter) \
    DECLARE_IMPL_NAME(ImplD3DKMTCreateAllocation) \
    DECLARE_IMPL_NAME(ImplD3DKMTCreateContext) \
    DECLARE_IMPL_NAME(ImplD3DKMTCreateDevice) \
    DECLARE_IMPL_NAME(ImplD3DKMTCreateSynchronizationObject) \
    DECLARE_IMPL_NAME(ImplD3DKMTDestroyAllocation) \
    DECLARE_IMPL_NAME(ImplD3DKMTDestroyContext) \
    DECLARE_IMPL_NAME(ImplD3DKMTDestroyDevice) \
    DECLARE_IMPL_NAME(ImplD3DKMTDestroySynchronizationObject) \
    DECLARE_IMPL_NAME(ImplD3DKMTEscape) \
    DECLARE_IMPL_NAME(ImplD3DKMTGetContextSchedulingPriority) \
    DECLARE_IMPL_NAME(ImplD3DKMTGetDeviceState) \
    DECLARE_IMPL_NAME(ImplD3DKMTGetDisplayModeList) \
    DECLARE_IMPL_NAME(ImplD3DKMTGetMultisampleMethodList) \
    DECLARE_IMPL_NAME(ImplD3DKMTGetRuntimeData) \
    DECLARE_IMPL_NAME(ImplD3DKMTGetSharedPrimaryHandle) \
    DECLARE_IMPL_NAME(ImplD3DKMTLock) \
    DECLARE_IMPL_NAME(ImplD3DKMTOpenAdapterFromHdc) \
    DECLARE_IMPL_NAME(ImplD3DKMTOpenResource) \
    DECLARE_IMPL_NAME(ImplD3DKMTPresent) \
    DECLARE_IMPL_NAME(ImplD3DKMTQueryAdapterInfo) \
    DECLARE_IMPL_NAME(ImplD3DKMTQueryAllocationResidency) \
    DECLARE_IMPL_NAME(ImplD3DKMTQueryResourceInfo) \
    DECLARE_IMPL_NAME(ImplD3DKMTRender) \
    DECLARE_IMPL_NAME(ImplD3DKMTSetAllocationPriority) \
    DECLARE_IMPL_NAME(ImplD3DKMTSetContextSchedulingPriority) \
    DECLARE_IMPL_NAME(ImplD3DKMTSetDisplayMode) \
    DECLARE_IMPL_NAME(ImplD3DKMTSetDisplayPrivateDriverFormat) \
    DECLARE_IMPL_NAME(ImplD3DKMTSetGammaRamp) \
    DECLARE_IMPL_NAME(ImplD3DKMTSetVidPnSourceOwner) \
    DECLARE_IMPL_NAME(ImplD3DKMTSignalSynchronizationObject) \
    DECLARE_IMPL_NAME(ImplD3DKMTUnlock) \
    DECLARE_IMPL_NAME(ImplD3DKMTWaitForSynchronizationObject) \
    DECLARE_IMPL_NAME(ImplD3DKMTWaitForVerticalBlankEvent) \
    DECLARE_IMPL_NAME(ImplD3DPerformance_BeginEvent) \
    DECLARE_IMPL_NAME(ImplD3DPerformance_EndEvent) \
    DECLARE_IMPL_NAME(ImplD3DPerformance_GetStatus) \
    DECLARE_IMPL_NAME(ImplD3DPerformance_SetMarker) \
    DECLARE_IMPL_NAME(ImplEnableFeatureLevelUpgrade) \
    DECLARE_IMPL_NAME(ImplOpenAdapter10) \
    DECLARE_IMPL_NAME(ImplOpenAdapter10_2) \

namespace D3D11Exports {
    constexpr std::array<std::string_view, 51> GetAllImplNames() {
        return { D3D11_IMPL_FUNCTION_LIST };
    }
}