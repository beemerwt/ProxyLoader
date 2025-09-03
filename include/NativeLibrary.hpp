#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <string>
#include <stdexcept>
#include <type_traits>

static HMODULE LoadSystemLibrary(const char* dllName) {
    char systemPath[MAX_PATH];
    if (!GetSystemDirectoryA(systemPath, MAX_PATH))
        return nullptr;

    std::string fullPath = std::string(systemPath) + "\\" + dllName;
    return LoadLibraryA(fullPath.c_str());
}

class NativeLibrary {
public:
    explicit NativeLibrary(HMODULE handle) {
        if (!handle)
            throw std::invalid_argument("NativeLibrary handle is null");
        libHandle = handle;
    }

    ~NativeLibrary() {
        if (libHandle != nullptr) {
            FreeLibrary(libHandle);
            libHandle = nullptr; // clear
        }
    }

    static HMODULE Load(const std::string& path) {
        if (path.empty())
            throw std::invalid_argument("path is empty");

        HMODULE h = LoadLibraryA(path.c_str());
        if (!static_cast<bool>(h))
            throw std::runtime_error("Failed to load library: " + path);
        return h;
    }

    static bool TryLoad(const std::string& path, HMODULE* outLib) {
        try {
            *outLib = Load(path);
            return true;
        }
        catch (const std::exception& e) {
            return false;
        }
    }

    FARPROC GetExport(const std::string& name) const {
        if (name.empty())
            throw std::invalid_argument("export name is empty");

        FARPROC fp = GetProcAddress(libHandle, name.c_str()); // HMODULE -> FARPROC
        if (!fp)
            throw std::runtime_error("Export not found: " + name);
        return fp;
    }

    // FIX: first parameter must be the LIB handle, not a proc handle
    static bool TryGetExport(HMODULE lib, const std::string& name, void** outFunc) {
        if (lib == nullptr || name.empty() || !outFunc)
            return false;

        FARPROC fp = GetProcAddress(lib, name.c_str());
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
    HMODULE libHandle{};
};
