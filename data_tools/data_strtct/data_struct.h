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
struct UserData
{
    uint64 id;
    uint64 data;

    /**
     * 比较运算符（按 id 比较）
     */
    bool operator<(const UserData &other) const;
    /**
     * 日志打印用户信息
     */
    void log_info() const;
    /**
     * 重载输出流运算符
     */
    friend std::ostream &operator<<(std::ostream &os, const UserData &u);
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