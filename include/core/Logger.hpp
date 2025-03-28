#pragma once

#include <string>
#include <fstream>
#include <mutex>

namespace core {

enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error
};

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void setLogFile(const std::string& filename) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_logFile.open(filename, std::ios::app);
    }

    void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::string levelStr;
        switch (level) {
            case LogLevel::Debug: levelStr = "DEBUG"; break;
            case LogLevel::Info: levelStr = "INFO"; break;
            case LogLevel::Warning: levelStr = "WARNING"; break;
            case LogLevel::Error: levelStr = "ERROR"; break;
        }

        std::string logMessage = "[" + levelStr + "] " + message + "\n";
        std::cout << logMessage;
        if (m_logFile.is_open()) {
            m_logFile << logMessage;
            m_logFile.flush();
        }
    }

    ~Logger() {
        if (m_logFile.is_open()) {
            m_logFile.close();
        }
    }

private:
    Logger() = default;
    std::ofstream m_logFile;
    std::mutex m_mutex;
};

// Convenience macros for logging
#define LOG_DEBUG(msg) Logger::getInstance().log(LogLevel::Debug, msg)
#define LOG_INFO(msg) Logger::getInstance().log(LogLevel::Info, msg)
#define LOG_WARNING(msg) Logger::getInstance().log(LogLevel::Warning, msg)
#define LOG_ERROR(msg) Logger::getInstance().log(LogLevel::Error, msg)

} // namespace core 