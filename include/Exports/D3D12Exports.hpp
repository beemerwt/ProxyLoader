#pragma once
#include "Exports.hpp"
#define D3D12_IMPL_FUNCTION_LIST \
    DECLARE_IMPL_NAME(ImplD3D12CoreCreateLayeredDevice) \
    DECLARE_IMPL_NAME(ImplD3D12CoreGetLayeredDeviceSize) \
    DECLARE_IMPL_NAME(ImplD3D12CoreRegisterLayers) \
    DECLARE_IMPL_NAME(ImplD3D12CreateDevice) \
    DECLARE_IMPL_NAME(ImplD3D12CreateRootSignatureDeserializer) \
    DECLARE_IMPL_NAME(ImplD3D12CreateVersionedRootSignatureDeserializer) \
    DECLARE_IMPL_NAME(ImplD3D12DeviceRemovedExtendedData) \
    DECLARE_IMPL_NAME(ImplD3D12EnableExperimentalFeatures) \
    DECLARE_IMPL_NAME(ImplD3D12GetDebugInterface) \
    DECLARE_IMPL_NAME(ImplD3D12GetInterface) \
    DECLARE_IMPL_NAME(ImplD3D12PIXEventsReplaceBlock) \
    DECLARE_IMPL_NAME(ImplD3D12PIXGetThreadInfo) \
    DECLARE_IMPL_NAME(ImplD3D12PIXNotifyWakeFromFenceSignal) \
    DECLARE_IMPL_NAME(ImplD3D12PIXReportCounter) \
    DECLARE_IMPL_NAME(ImplD3D12SerializeRootSignature) \
    DECLARE_IMPL_NAME(ImplD3D12SerializeVersionedRootSignature) \
    DECLARE_IMPL_NAME(ImplGetBehaviorValue) \
    DECLARE_IMPL_NAME(ImplSetAppCompatStringPointer) \

namespace D3D12Exports {
    constexpr std::array<std::string_view, 18> GetAllImplNames() {
        return { D3D12_IMPL_FUNCTION_LIST };
    }
}
