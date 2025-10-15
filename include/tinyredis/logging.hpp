#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <functional>
#include <iostream>
#include <mutex>
#include <ostream>
#include <sstream>

namespace tinyredis
{
#define LOG_FATAL(...) log(LogLevel::Fatal, __VA_ARGS__)

    enum class LogLevel : uint8_t
    {
        Trace = 0,
        Debug = 1,
        Info = 2,
        Warning = 3,
        Error = 4,
        Fatal = 5,
    };

    std::ostream& operator<<(std::ostream& os, LogLevel logLevel)
    {
        switch (logLevel) {
        case LogLevel::Trace:
            os << "[TRACE]";
            break;
        case LogLevel::Debug:
            os << "[DEBUG]";
            break;
        case LogLevel::Info:
            os << "[INFO]";
            break;
        case LogLevel::Warning:
            os << "[WARN]";
            break;
        case LogLevel::Error:
            os << "[ERROR]";
            break;
        case LogLevel::Fatal:
            os << "[FATAL]";
            break;
        default:
            os << "[UNKNOWN]";
            break;
        }

        return os;
    }

    inline auto gLogLevel = LogLevel::Info;

    // Decided to use a template instead of va_args as the latter requires a formatted print
    // to intermediary buffer.
    template <typename... Args> inline void log(LogLevel logLevel, Args&&... args)
    {
        static std::mutex logMtx;

        if (logLevel >= gLogLevel) {
            std::ostringstream ss;
            ss << logLevel;
            (ss << ... << args) << '\n';

            auto logMsg = ss.str();

            std::lock_guard lk{logMtx};
            std::cout << logMsg;
        }

        if (logLevel == LogLevel::Fatal)
            exit(1);
    }

} // namespace tinyredis