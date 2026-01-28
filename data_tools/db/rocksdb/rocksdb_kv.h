#ifndef ROCKSDB_KV_H
#define ROCKSDB_KV_H

#include <cstdint>
#include <string>
#include <vector>
#include <rocksdb/db.h>

#include "data_tools/data_strtct/data_struct.h"

/**
 * RocksDB 键值存储封装类
 */
class RocksDBKV
{
public:
    /**
     * 构造函数，打开指定路径的 RocksDB 数据库
     * @param path RocksDB 数据库路径
     */
    explicit RocksDBKV(const std::string &path);
    ~RocksDBKV();

    /**
     * 批量写入一个 bucket
     * @param bucket_id bucket ID
     * @param users 该 bucket 内的用户数据列表
     */
    void put_bucket(uint64 bucket_id,
                    const std::vector<UserData> &users);

    /**
     * 扫描并返回指定 bucket 内的所有用户数据
     * @param bucket_id bucket ID
     * @return 该 bucket 内的用户数据列表
     */
    std::vector<UserData> scan_bucket(uint64 bucket_id);

private:
    // RocksDB 数据库实例
    rocksdb::DB *db_;

    /**
     * 编码键值对的键
     * @param bucket_id bucket ID
     * @param user_id 用户 ID
     * @return 编码后的键字符串
     */
    static std::string encode_key(uint64 bucket_id, uint64 user_id);
};

#endif // ROCKSDB_KV_H