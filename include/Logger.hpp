#pragma once
#include <iostream>
#include <fstream>
#include <streambuf>
#include <memory>
#include <string>
#include <codecvt>
#include <locale>
#include <sstream>
#include <Windows.h>

static const std::string GetLogTimeName() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    std::ostringstream oss;
    oss << "log-" << st.wYear << "-" << st.wMonth << "-" << st.wDay
        << "_" << st.wHour << "-" << st.wMinute << "-" << st.wSecond << ".txt";
    return oss.str();
}

class Logger {
public:
    static constexpr size_t LineSize = 128;

    static Logger& Instance();
    void Start(const std::string& filePath = "proxyloader.txt");
    void Stop();

    void NullHandles()
    {
        SetStdHandle(STD_OUTPUT_HANDLE, 0);
        SetStdHandle(STD_ERROR_HANDLE, 0);
    }

    void ResetHandles()
    {
        SetStdHandle(STD_OUTPUT_HANDLE, outputHandle);
        SetStdHandle(STD_ERROR_HANDLE, outputHandle);
    }

    static void Log(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        Instance().vLog(fmt, args);
        va_end(args);
    }

    static void SetHeader(const std::string& header) {
        Instance().header = header;
    }

private:
    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void EnsureConsole();

    void vLog(const char* fmt, va_list args) {
        char line[LineSize];
        vsnprintf(line, LineSize, fmt, args);
        std::cout << header << " " << line << std::endl;
    }

    struct TeeCoutBuf : public std::streambuf {
        std::streambuf* consoleBuf;
        std::ostream& file;
        TeeCoutBuf(std::streambuf* console, std::ostream& f) : consoleBuf(console), file(f) {}

        int overflow(int c) override {
            if (c == EOF) return !EOF;
            consoleBuf->sputc(c);
            file.put(static_cast<char>(c));
            return c;
        }

        int sync() override {
            consoleBuf->pubsync();
            file.flush();
            return 0;
        }
    };

    std::ofstream fileStream;
    std::unique_ptr<TeeCoutBuf> coutBuf;
    std::streambuf* oldCoutBuf = nullptr;
    std::string header = "";
    HANDLE outputHandle = nullptr;
    bool active = false;
    bool hasOwnWindow = false;
    bool allocatedConsole = false;
};
