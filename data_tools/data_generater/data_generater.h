#ifndef DATA_GENERATER_H
#define DATA_GENERATER_H

#include <vector>
#include <cstdint>
#include "data_tools/data_struct/data_struct.h"

using uint64 = uint64_t;

/**
 * 用于生成一个随机的 64 位无符号整数。
 * @return 随机生成的 64 位无符号整数
 */
uint64 random_uint64();

/**
 * 生成随机用户数据
 * @param users 存储生成数据的向量
 * @param size 要生成的用户数量
 * @param seed 随机数生成器种子（可选，默认使用随机设备）
 */
void generate_users_data(std::vector<UserData<uint64,uint64>>& users, size_t size, uint64 seed = 0);

/**
 * 生成指定范围内的随机用户数据
 * @param users 存储生成数据的向量
 * @param size 要生成的用户数量
 * @param data_min 数据的最小值
 * @param data_max 数据的最大值
 * @param seed 随机数生成器种子
 */
void generate_users_data_range(std::vector<UserData<uint64,uint64>>& users, size_t size, 
                               uint64 data_min, uint64 data_max, uint64 seed = 0);


/**
 * 数据分桶
 * @param users 输入的用户数据向量
 * @param buckets 输出的分桶结果，每个桶是一个用户数据向量
 * @param bucket_count 桶的数量
 */

void bucketize_users_data(const std::vector<UserData<uint64,uint64>> &users,
                          std::vector<std::vector<UserData<uint64,uint64>>> &buckets,
                          size_t bucket_count);

#endif // DATA_GENERATER_H