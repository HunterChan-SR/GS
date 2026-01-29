#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <cstdint>
#include <cstddef>
#include <sstream>
#include "logger/logger.h"
/**
 * 通用数据结构定义
 */
using uint64 = uint64_t;
using int64 = int64_t;

/**
 * 用户数据结构体
 */
template <typename T1, typename T2>
struct UserData
{
    T1 id;
    T2 data;

    /**
     * 比较运算符（按 id 比较）
     */
    bool operator<(const UserData &other) const
    {
        return this->id < other.id;
    }
    /**
     * 日志打印用户信息
     */
    void log_info() const
    {
        Logger::Info("UserData { id: " + std::to_string(id) + ", data: " + std::to_string(data) + " }");
    }
    /**
     * 重载输出流运算符
     */
    friend std::ostream &operator<<(std::ostream &os, const UserData &u)
    {
        os << "UserData { id: " << u.id << ", data: " << u.data << " }";
        return os;
    }
};

/**
 * 通用类型转换为字符串函数
 * @param v 任意类型变量
 * @return 字符串表示
 */
template <typename T>
std::string to_string_any(const T &v)
{
    std::ostringstream oss;
    oss << v;
    return oss.str();
}
#endif // DATA_STRUCT_H