#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <type_traits>

#if defined(_WIN32)
# define PLATFORM_LOAD_FROM_SYSTEM(lib) LoadSystemLibrary(lib.c_str())
# define PLATFORM_LOAD(lib) LoadLibraryA(lib.c_str())
# define PLATFORM_GETSYM(lib, sym) GetProcAddress(lib, sym)
# define PLATFORM_UNLOAD(lib) FreeLibrary(lib)
#define PLATFORM_MODULE HMODULE
#define PLATFORM_PROC   FARPROC

#elif defined(__linux__)
#include <dlfcn.h>
# define PLATFORM_LOAD(lib) dlopen(lib.c_str(), RTLD_NOW)
# define PLATFORM_GETSYM(lib, sym) dlsym(lib, sym)
# define PLATFORM_UNLOAD(lib) dlclose(lib)

struct LinHandle {
    void* handle;

    bool empty() const {
        return handle == nullptr;
    }

    operator void* () const {
        return handle;
    }
};

#define PLATFORM_HANDLE LinHandle

#else
# error Unsupported platform
#endif

static PLATFORM_MODULE LoadSystemLibrary(const char* dllName) {
    char systemPath[MAX_PATH];
    if (!GetSystemDirectoryA(systemPath, MAX_PATH))
        return nullptr;

    std::string fullPath = std::string(systemPath) + "\\" + dllName;
    return LoadLibraryA(fullPath.c_str());
}

class NativeLibrary {
public:
    explicit NativeLibrary(PLATFORM_MODULE handle) {
        if (!handle)
            throw std::invalid_argument("NativeLibrary handle is null");
        libHandle = handle;
    }

    ~NativeLibrary() {
        if (libHandle != nullptr) {
            PLATFORM_UNLOAD(libHandle);
            libHandle = nullptr; // clear
        }
    }

    static PLATFORM_MODULE Load(const std::string& path) {
        if (path.empty())
            throw std::invalid_argument("path is empty");

        PLATFORM_MODULE h{ PLATFORM_LOAD(path) };
        if (!static_cast<bool>(h))
            throw std::runtime_error("Failed to load library: " + path);
        return h;
    }

    static bool TryLoad(const std::string& path, PLATFORM_MODULE* outLib) {
        try {
            *outLib = Load(path);
            return true;
        }
        catch (const std::exception& e) {
            std::cout << "Error loading library: " << e.what() << std::endl;
            return false;
        }
    }

    PLATFORM_PROC GetExport(const std::string& name) const {
        if (name.empty())
            throw std::invalid_argument("export name is empty");

        PLATFORM_PROC fp = PLATFORM_GETSYM(libHandle, name.c_str()); // HMODULE -> FARPROC
        if (!fp)
            throw std::runtime_error("Export not found: " + name);
        return PLATFORM_PROC{ fp };
    }

    // FIX: first parameter must be the LIB handle, not a proc handle
    static bool TryGetExport(PLATFORM_MODULE lib, const std::string& name, void** outFunc) {
        if (lib == nullptr || name.empty() || !outFunc)
            return false;

        PLATFORM_PROC fp = PLATFORM_GETSYM(lib, name.c_str());
        if (!fp) return false;

        *outFunc = reinterpret_cast<void*>(fp);
        return true;
    }

    template<typename Fn>
    Fn GetFunction(const std::string& name) {
        // Accept function pointer types only
        static_assert(std::is_pointer_v<Fn> && std::is_function_v<std::remove_pointer_t<Fn>>,
                      "Fn must be a function pointer type");
        return reinterpret_cast<Fn>(GetExport(name));
    }

protected:
    PLATFORM_MODULE libHandle{};
};
