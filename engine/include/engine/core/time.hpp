#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>

namespace timeu{
    std::string getCurrentTimeHM(){
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf;
#if defined(_WIN32) || defined(_WIN64)
        localtime_s(&tm_buf, &time);
#else
        localtime_r(&time, &tm_buf);
#endif
        std::ostringstream ss;
        ss << std::put_time(&tm_buf, "%H:%M:%S");
        return ss.str();
    }
};

#endif // TIME_HPP