#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <debugapi.h>
#include "NativeLibrary.hpp"

namespace ProxyResolver {
void Init(HMODULE hModule);
void PatchExport(void* theirExport, void* ourExport);
void CreateExport(HMODULE ourHandle, HMODULE ogHandle, const std::string_view& method);

template<size_t N>
void CreateExports(HMODULE ourHandle,
    HMODULE ogHandle, std::array<std::string_view, N> methods)
{
    for (size_t i = 0; i < N; ++i)
        CreateExport(ourHandle, ogHandle, methods[i]);
}
};