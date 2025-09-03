#pragma once
#ifdef _DEBUG
#include <debugapi.h>
#include <cstdio>
#include <cstdarg>

inline void LOG(const char* format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    OutputDebugStringA(buffer);
}
#else
#define LOG(...)
#endif
