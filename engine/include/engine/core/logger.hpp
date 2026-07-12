#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <mutex>
#include <sstream>
#include <iomanip>

#include "time.hpp"

enum class LogLevel{
    DEBUG,
    INFO,
    ERR
};

class Logger{
private:
    Logger() :_minLevel(LogLevel::DEBUG) {}
    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(const Logger&&) = delete;
    Logger& operator=(const Logger&&) = delete;

    std::string _prefix = "[SVAROG] -> ";
    LogLevel _minLevel;
    std::mutex _mutex;

    std::string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::ERR:return "ERROR";
            default: return "NONE";
        }
    }
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    void setLogLevel(LogLevel level) {
        std::lock_guard<std::mutex> lock(_mutex);
        _minLevel = level;
    }
    void log(LogLevel lvl, const std::string& msg, const std::string& file, int line){
        std::lock_guard<std::mutex> lock(_mutex);
        if (lvl < _minLevel){ return; }
        std::cout<<_prefix
            <<"["<< timeu::getCurrentTimeHM() <<"] "
            <<"<"<< levelToString(lvl) <<"> "
            <<"{"<<file <<":"<<line <<"}: "
            <<msg<<std::endl;
    }

};
class LogMessage {
public:
    LogMessage(LogLevel level, const std::string& file, int line)
        : level_(level), file_(file), line_(line) {}

    ~LogMessage() {
        Logger::getInstance().log(level_, stream_.str(), file_, line_);
    }
    template <typename T>
    LogMessage& operator<<(const T& value) {
        stream_ << value;
        return *this;
    }

private:
    std::ostringstream stream_;
    LogLevel level_;
    std::string file_;
    int line_;
};

#define LOG_DEBUG(msg) LogMessage(LogLevel::DEBUG, __FILE__, __LINE__) << msg
#define LOG_INFO(msg) LogMessage(LogLevel::INFO, __FILE__, __LINE__) << msg
#define LOG_ERR(msg) LogMessage(LogLevel::ERR, __FILE__, __LINE__) << msg

#endif // LOGGER_HPP