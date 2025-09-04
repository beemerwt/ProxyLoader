// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <Shlwapi.h>
#include <MinHook.h>
#include <string>
#include "ProxyMap.hpp"
#include "Logger.hpp"
#include "ProxyResolver.hpp"

#define MOD_PATH "C:\\Users\\Beemer\\HKIAInfiniteGift\\x64\\Release\\HKIAInfiniteGift.dll" // Change this to your mod DLL path
#define GAMEASSEMBLY L"GameAssembly.dll" // Change this if the target game uses a different name
#define GAME_PROCESS "Hello Kitty.exe" // Change this to your target process name

using il2cpp_init_fn = void* (__cdecl*)(void*);
using il2cpp_runtime_invoke_fn = void* (__cdecl*)(void*, void*, void**, void*);
using il2cpp_method_get_name_fn = const char* (__cdecl*)(void*);

// Function pointers
static LPVOID orig_il2cpp_init = nullptr;
static LPVOID orig_runtime_invoke = nullptr;

// Trampolines
static il2cpp_init_fn il2cpp_init = nullptr;
static il2cpp_runtime_invoke_fn il2cpp_runtime_invoke = nullptr;
static il2cpp_method_get_name_fn il2cpp_method_get_name = nullptr;

bool modStarted = false;
void(*startFunc)() = nullptr;

bool IsRestartStubProcess() {
    std::string cmd = GetCommandLineA();
    return cmd.find("--steam") != std::string::npos || cmd.find("--attach") != std::string::npos;
}

static bool IsTargetGameProcess() {
    char path[MAX_PATH] = {};
    GetModuleFileNameA(nullptr, path, MAX_PATH);

    std::string filename = path;
    size_t lastSlash = filename.find_last_of("\\/");
    if (lastSlash != std::string::npos)
        filename = filename.substr(lastSlash + 1);

    return filename == GAME_PROCESS;
}

void* __cdecl Il2CppRuntimeInvokeHook(void* method, void* obj, void** args, void* exc) {
    if (!il2cpp_method_get_name)
        return 0;

    auto result = il2cpp_runtime_invoke(method, obj, args, exc);
    const char* name = il2cpp_method_get_name(method);
    if (!name || !strstr(name, "Internal_ActiveSceneChanged"))
        return result;

    MH_DisableHook(orig_runtime_invoke);
    MH_RemoveHook(orig_runtime_invoke);

    LOG("Invoke hijacked : %s", name);
    return result;
}

void* __cdecl Il2CppInitHook(void* domain) {
    LOG("il2cpp_init hook called");

    void* result = il2cpp_init(domain);
    MH_DisableHook(orig_il2cpp_init);
    MH_RemoveHook(orig_il2cpp_init);

    HMODULE gameAssembly = GetModuleHandleA("GameAssembly.dll");
    if (!gameAssembly) return result;

    orig_runtime_invoke = reinterpret_cast<LPVOID>(GetProcAddress(gameAssembly, "il2cpp_runtime_invoke"));
    il2cpp_method_get_name = reinterpret_cast<il2cpp_method_get_name_fn>(
        GetProcAddress(gameAssembly, "il2cpp_method_get_name"));

    if (orig_runtime_invoke != nullptr && il2cpp_method_get_name != nullptr) {
        LPVOID runtimeHook = reinterpret_cast<LPVOID>(&Il2CppRuntimeInvokeHook);
        MH_CreateHook(orig_runtime_invoke, runtimeHook, reinterpret_cast<LPVOID*>(&il2cpp_runtime_invoke));
        MH_EnableHook(orig_runtime_invoke);
        LOG("Hooked il2cpp_runtime_invoke");
    }

    return result;
}

// Optional exported native hooks
extern "C" __declspec(dllexport) void __cdecl NativeHookAttach(void** target, void* detour) {
    MH_CreateHook(*target, detour, nullptr);
    MH_EnableHook(*target);
}

extern "C" __declspec(dllexport) void __cdecl NativeHookDetach(void** target, void* detour) {
    MH_DisableHook(*target);
    MH_RemoveHook(*target);
}

static DWORD WINAPI HookThread(LPVOID hModule) {
    ProxyResolver::Init(reinterpret_cast<HMODULE>(hModule));
    
    if (MH_Initialize() != MH_OK) {
        LOG("Failed to initialize MinHook");
        return 1;
    }

    if (MH_CreateHookApiEx(GAMEASSEMBLY, "il2cpp_init", (LPVOID)&Il2CppInitHook,
        (LPVOID*)&il2cpp_init, (LPVOID*)&orig_il2cpp_init) != MH_OK) {
        LOG("Failed to create il2cpp_init hook");
        return 1;
    }

    if (MH_EnableHook(orig_il2cpp_init) != MH_OK) {
        LOG("Failed to enable il2cpp_init hook");
        return 1;
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        if (!IsTargetGameProcess()) return TRUE;
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, HookThread, hModule, 0, nullptr);
    }
}