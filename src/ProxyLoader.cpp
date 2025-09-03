// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <Shlwapi.h>
#include <MinHook.h>
#include <iostream>
#include <string>
#include "Logger.hpp"
#include "ProxyMap.hpp"
#include "ProxyResolver.hpp"

#define MOD_PATH "C:\\Users\\Beemer\\HKIAInfiniteGift\\x64\\Release\\HKIAInfiniteGift.dll"
#define GAME_PROCESS "Hello Kitty.exe"

using il2cpp_init_fn = void* (__cdecl*)(void*);
using il2cpp_runtime_invoke_fn = void* (__cdecl*)(void*, void*, void**, void*);
using il2cpp_method_get_name_fn = const char* (__cdecl*)(void*);

// Function pointers
il2cpp_init_fn orig_il2cpp_init = nullptr;
il2cpp_runtime_invoke_fn orig_runtime_invoke = nullptr;
il2cpp_method_get_name_fn il2cpp_method_get_name = nullptr;

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

    // Adjust for your game EXE
    return filename == GAME_PROCESS;
}

void LoadManagedMod() {
    if (modStarted) return;
    modStarted = true;

    Logger::Log("Loading mod from %s", MOD_PATH);
    LoadLibraryA(MOD_PATH);
}

bool g_FinalLoad = false;

void* __cdecl Il2CppRuntimeInvokeHook(void* method, void* obj, void** args, void* exc) {
    if (!il2cpp_method_get_name)
        return 0;

    auto result = orig_runtime_invoke(method, obj, args, exc);

    const char* name = il2cpp_method_get_name(method);
    if (!name || !strstr(name, "Internal_ActiveSceneChanged"))
        return result;


    MH_DisableHook(reinterpret_cast<void*>(orig_runtime_invoke));
    MH_RemoveHook(reinterpret_cast<void*>(orig_runtime_invoke));

    Logger::Log("Invoke hijacked : %s", name);
    LoadManagedMod();
    return result;
}

void* __cdecl Il2CppInitHook(void* domain) {
    Logger::Instance().ResetHandles();
    Logger::Log("il2cpp_init hook called");

    void* result = orig_il2cpp_init(domain);
    MH_DisableHook(reinterpret_cast<void*>(orig_il2cpp_init));
    MH_RemoveHook(reinterpret_cast<void*>(orig_il2cpp_init));

    HMODULE gameAssembly = GetModuleHandleA("GameAssembly.dll");
    if (!gameAssembly) return result;

    FARPROC invokePtr = GetProcAddress(gameAssembly, "il2cpp_runtime_invoke");
    FARPROC namePtr = GetProcAddress(gameAssembly, "il2cpp_method_get_name");
    LPVOID runtimeHook = reinterpret_cast<LPVOID>(Il2CppRuntimeInvokeHook);

    if (invokePtr != nullptr && namePtr != nullptr) {
        il2cpp_method_get_name = reinterpret_cast<il2cpp_method_get_name_fn>(namePtr);
        MH_CreateHook(reinterpret_cast<void*>(invokePtr), runtimeHook, reinterpret_cast<LPVOID*>(&orig_runtime_invoke));
        MH_EnableHook(reinterpret_cast<void*>(invokePtr));

        Logger::Log("Hooked il2cpp_runtime_invoke");
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

bool hooksInitiated = false;
bool SetupHooks() {
    MH_Initialize();

    HMODULE gameAssembly = LoadLibraryW(L"GameAssembly.dll");
    if (!gameAssembly) {
        Logger::Log("Failed to load GameAssembly.dll");
        return false;
    }

    FARPROC initPtr = GetProcAddress(gameAssembly, "il2cpp_init");
    LPVOID initHook = reinterpret_cast<LPVOID>(Il2CppInitHook);
    if (!initPtr) return false;

    MH_CreateHook(reinterpret_cast<LPVOID>(initPtr), initHook, reinterpret_cast<LPVOID*>(&orig_il2cpp_init));
    MH_EnableHook(reinterpret_cast<LPVOID>(initPtr));
    return true;
}

void Init(HMODULE hModule) {
    // Initialize the logger
    Logger::Instance().Start(GetLogTimeName());
    Logger::SetHeader("[ProxyLoader]");
    Logger::Log("Probing il2cpp_init");

    if (SetupHooks())
        Logger::Instance().NullHandles();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID) {
    if (ulReasonForCall != DLL_PROCESS_ATTACH)
        return TRUE;

    if (!IsTargetGameProcess()) {
        std::cout << "[ProxyLoader] Not a target game process" << std::endl;
        return TRUE;
    }

    ProxyResolver::Init(hModule);
    Init(hModule);
    return TRUE;
}