#pragma once

#define LOG(status, ...) logger::log(status, __FILE__, __LINE__, __TIME__, __VA_ARGS__)
#define INFO(...) LOG(logger::INFO, __VA_ARGS__)
#define WARN(...) LOG(logger::WARNING, __VA_ARGS__)
#define ERR(...) LOG(logger::ERROR, __VA_ARGS__)

namespace logger{
    const int INFO = 0, WARNING = 1, ERROR = 2;

    void log(int mode, const char* file, int line, const char* time, const char* fmt, ...);
}
