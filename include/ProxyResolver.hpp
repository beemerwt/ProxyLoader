#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include "NativeLibrary.hpp"

namespace ProxyResolver {
void Init(PLATFORM_MODULE hModule);
void PatchExport(void* theirExport, void* ourExport);
void CreateExport(PLATFORM_MODULE ourHandle, PLATFORM_MODULE ogHandle, const std::string_view& method);

template<size_t N>
void CreateExports(PLATFORM_MODULE ourHandle,
    PLATFORM_MODULE ogHandle, std::array<std::string_view, N> methods)
{
    for (size_t i = 0; i < N; ++i)
        CreateExport(ourHandle, ogHandle, methods[i]);
}
};