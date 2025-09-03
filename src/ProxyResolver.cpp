// ProxyResolver.cpp
// C++ equivalent of MelonLoader's ProxyResolver for replacing DLL exports at runtime
#include <shlobj.h>
#include <string_view>
#include <filesystem>
#include <KnownFolders.h>
#include "Logger.hpp"
#include "ProxyMap.hpp"
#include "NativeLibrary.hpp"
#include "ProxyResolver.hpp"
#define MODULE_EXTENSION ".dll"

namespace ProxyResolver {
void MapProxyByName(PLATFORM_MODULE ourHandle, PLATFORM_MODULE ogHandle, std::string_view name);

// theirExport = src, ourExport = dst
void PatchExport(void* theirExport, void* ourExport) {
#if defined(_M_X64)
    // mov r11, <addr>; jmp r11
    BYTE shellcode[] = {
        0x49, 0xBB,                         // mov r11, <addr>
        0, 0, 0, 0, 0, 0, 0, 0,             // (addr)
        0x41, 0xFF, 0xE3                    // jmp r11
    };
    memcpy(&shellcode[2], &theirExport, sizeof(void*));
#else
    // mov eax, <addr>; jmp eax
    BYTE shellcode[] = {
        0xB8,                               // mov eax, <addr>
        0, 0, 0, 0,                         // (addr)
        0xFF, 0xE0                          // jmp eax
    };
    memcpy(&shellcode[1], &theirExport, sizeof(void*));
#endif

    DWORD oldProtect;
    VirtualProtect(ourExport, sizeof(shellcode), PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(ourExport, shellcode, sizeof(shellcode));
    FlushInstructionCache(GetCurrentProcess(), ourExport, sizeof(shellcode));
    VirtualProtect(ourExport, sizeof(shellcode), oldProtect, &oldProtect);
}

void CreateExport(PLATFORM_MODULE ourHandle, PLATFORM_MODULE ogHandle,
    const std::string_view& method)
{
    const char* preTag = "Impl";
    if (!method.starts_with(preTag)) {
        Logger::Log("Method does not start with Impl: %s", method);
        return;
    }

    // Yea, I know it's bad lol
    std::string _export = method.substr(strlen(preTag)).data();

    void* theirExport = nullptr;
    void* ourExport = nullptr;
    if (!NativeLibrary::TryGetExport(ogHandle, _export, &theirExport)
        || !NativeLibrary::TryGetExport(ourHandle, _export, &ourExport))
    {
        Logger::Log("Failed to get export: %s", _export.c_str());
        return;
    }

    PatchExport(theirExport, ourExport);
}

std::filesystem::path GetSystemFolderPath() {
    PWSTR sysPath = nullptr;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_System, 0, nullptr, &sysPath))) {
        std::filesystem::path result(sysPath);
        CoTaskMemFree(sysPath);
        return result;
    }
    return {};
}

bool LoadModule(const std::filesystem::path& filePath, PLATFORM_MODULE* handle)
{
    if (!std::filesystem::exists(filePath))
        return false;

    return NativeLibrary::TryLoad(filePath.string(), handle);
}

bool LoadModuleFromLocalCopy(const std::filesystem::path& basePath, const std::string& fileName,
    const std::string tag, PLATFORM_MODULE* handle)
{
    if (basePath.empty())
        return false;

    auto filePath = basePath / (fileName + tag + MODULE_EXTENSION);
    Logger::Log("Loading Module from Local Copy: %s", filePath.string().c_str());
    return LoadModule(filePath, handle);
}

bool LoadModuleFromSystemCopy(const std::string& fileName, PLATFORM_MODULE* handle)
{
    auto systemFolder = GetSystemFolderPath();
    auto filePath = systemFolder / (fileName + MODULE_EXTENSION);
    Logger::Log("Loading Module from System: %s", filePath.string().c_str());
    return LoadModule(filePath, handle);
}

void Init(PLATFORM_MODULE ourHandle) {
    char path[MAX_PATH];
    if (GetModuleFileNameA(ourHandle, path, MAX_PATH) == 0)
        return;

    Logger::Log("Module File Name: %s", path);

    std::string ourName = std::filesystem::path(path).stem().string();
    std::string basePath = std::filesystem::path(path).parent_path().string();

    PLATFORM_MODULE ogHandle;
    if (!LoadModuleFromLocalCopy(basePath, ourName, "_original", &ogHandle)
        && !LoadModuleFromSystemCopy(ourName, &ogHandle)) {
        Logger::Log("Failed to load modules for %s", ourName.c_str());
        return;
    }

    Logger::Log("Modules loaded successfully.");
    Logger::Log("Creating exports...");

    auto shared = SharedExports::GetAllImplNames();
    for (size_t i = 0; i < shared.size(); ++i)
        CreateExport(ourHandle, ogHandle, shared[i]);

    MapProxyByName(ourHandle, ogHandle, ourName);
}

bool ichar_equals(char a, char b)
{
    return std::tolower(static_cast<unsigned char>(a)) ==
        std::tolower(static_cast<unsigned char>(b));
}

void MapProxyByName(PLATFORM_MODULE ourHandle, PLATFORM_MODULE ogHandle, std::string_view name)
{
    if (std::ranges::equal(name, "d3d10", ichar_equals))
        CreateExports(ourHandle, ogHandle, D3D10Exports::GetAllImplNames());

    else if (std::ranges::equal(name, "d3d11", ichar_equals))
        CreateExports(ourHandle, ogHandle, D3D11Exports::GetAllImplNames());

    else if (std::ranges::equal(name, "d3d12", ichar_equals))
        CreateExports(ourHandle, ogHandle, D3D12Exports::GetAllImplNames());

    else if (std::ranges::equal(name, "d3d8", ichar_equals))
        CreateExports(ourHandle, ogHandle, D3D8Exports::GetAllImplNames());

    else if (std::ranges::equal(name, "d3d9", ichar_equals))
        CreateExports(ourHandle, ogHandle, D3D9Exports::GetAllImplNames());

    else if (std::ranges::equal(name, "ddraw", ichar_equals))
        CreateExports(ourHandle, ogHandle, DDrawExports::GetAllImplNames());

    else if (std::ranges::equal(name, "dinput", ichar_equals))
        CreateExports(ourHandle, ogHandle, DInputExports::GetAllImplNames());

    else if (std::ranges::equal(name, "dinput8", ichar_equals))
        CreateExports(ourHandle, ogHandle, DInput8Exports::GetAllImplNames());

    else if (std::ranges::equal(name, "dsound", ichar_equals))
        CreateExports(ourHandle, ogHandle, DSoundExports::GetAllImplNames());

    else if (std::ranges::equal(name, "msacm32", ichar_equals))
        CreateExports(ourHandle, ogHandle, MSACM32Exports::GetAllImplNames());

    else if (std::ranges::equal(name, "version", ichar_equals) || name == "VERSION")
        CreateExports(ourHandle, ogHandle, VersionExports::GetAllImplNames());

    else if (std::ranges::equal(name, "winhttp", ichar_equals))
        CreateExports(ourHandle, ogHandle, WinHTTPExports::GetAllImplNames());

    else if (std::ranges::equal(name, "winmm", ichar_equals))
        CreateExports(ourHandle, ogHandle, WinMMExports::GetAllImplNames());

    else if (std::ranges::equal(name, "hkiainfinitegift", ichar_equals))
        Logger::Log("HKIA Infinite Gift module injected.");

    else
        Logger::Log("Unknown module name: %s", name);
}
}