#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <mutex>
#include <sstream>

/**
 * 日志级别枚举
 */
enum class LogLevel { INFO, WARN, ERROR };

/**
 * 获取当前时间字符串
 * @return 格式化的当前时间字符串
 */
inline std::string current_time_str() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto in_time_t = system_clock::to_time_t(now);
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S")
       << "." << std::setw(3) << std::setfill('0') << ms.count();
    return ss.str();
}

/**
 * 线程安全的日志记录类
 */
class Logger {
public:
    /**
     * 通用日志记录函数
     * @param level 日志级别
     * @param msg 日志消息
     */
    static void Log(LogLevel level, const std::string& msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::string ts = current_time_str();
        switch(level) {
            case LogLevel::INFO:  std::cout << ts << " [INFO] "; break;
            case LogLevel::WARN:  std::cout << ts << " [WARN] "; break;
            case LogLevel::ERROR: std::cerr << ts << " [ERROR] "; break;
        }
        if(level == LogLevel::ERROR)
            std::cerr << msg << std::endl;
        else
            std::cout << msg << std::endl;
    }
    /**
     * 信息级别日志
     * @param msg 日志消息
     */
    static void Info(const std::string& msg) { Log(LogLevel::INFO, msg); }
    /**
     * 警告级别日志
     * @param msg 日志消息
     */
    static void Warn(const std::string& msg) { Log(LogLevel::WARN, msg); }
    /**
     * 错误级别日志
     * @param msg 日志消息
     */
    static void Error(const std::string& msg) { Log(LogLevel::ERROR, msg); }

private:
    /**
     * 日志线程安全锁
     */
    static std::mutex mutex_;
};



#ifdef USE_GTEST
#include <gtest/gtest.h>
/**
 * 性能基准测试类
 */
class PerformanceBenchmark : public ::testing::Test {
protected:
    /**
     * 打印基准测试结果
     * @param test_name 测试名称
     * @param data_size 处理数据量
     * @param duration_ms 持续时间（毫秒）
     */
    void PrintBenchmarkResult(const std::string& test_name, size_t data_size, long long duration_ms) {
        double throughput = (double)data_size / (duration_ms / 1000.0);
        Logger::Info(std::string(50, '='));
        Logger::Info(test_name);
        Logger::Info(std::string(50, '-'));
        Logger::Info("  Data size: " + std::to_string(data_size) + " records");
        Logger::Info("  Duration: " + std::to_string(duration_ms) + " ms");
        Logger::Info("  Throughput: " + std::to_string(throughput / 1e6) + " million records/sec");
    }
};
#endif

#endif // LOGGER_H
