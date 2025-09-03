#include "Logger.hpp"
#include <io.h>
#include <fcntl.h>

Logger& Logger::Instance() {
    static Logger instance;
    return instance;
}

void Logger::EnsureConsole() {
    auto consoleWindow = GetConsoleWindow();
    auto stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (consoleWindow == 0 && stdOut == 0) {
        AllocConsole();
        consoleWindow = GetConsoleWindow();
        if (consoleWindow == 0)
            return;

        hasOwnWindow = true;
    }

    if (consoleWindow != 0)
        SetConsoleTitleW(L"HKIA ProxyLoader");

    // Set console code page to UTF-8
    SetConsoleOutputCP(CP_UTF8);

    allocatedConsole = true;

    FILE* dummy;
    freopen_s(&dummy, "CONOUT$", "w", stdout);
    freopen_s(&dummy, "CONOUT$", "w", stderr);

    std::cout.setf(std::ios::unitbuf);
    std::cerr.setf(std::ios::unitbuf);

    outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Logger::Start(const std::string& filePath) {
    if (active) return;

    EnsureConsole();

    fileStream.open(filePath, std::ios::binary | std::ios::app);
    if (!fileStream.is_open())
        throw std::runtime_error("Logger failed to open log file");

    oldCoutBuf = std::cout.rdbuf();
    coutBuf = std::make_unique<TeeCoutBuf>(oldCoutBuf, fileStream);

    std::cout.rdbuf(coutBuf.get());
    active = true;
}

void Logger::Stop() {
    if (!active) return;

    std::cout.rdbuf(oldCoutBuf);

    coutBuf.reset();
    fileStream.close();

    active = false;

    if (allocatedConsole) {
        FreeConsole();
        allocatedConsole = false;
    }
}

Logger::~Logger() {
    Stop();
}
