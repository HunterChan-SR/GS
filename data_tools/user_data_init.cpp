#include <vector>
#include <string>
#include <cstdlib>

#include "logger/logger.h"
#include "data_tools/data_generater/data_generater.h"
#include "data_tools/data_strtct/data_struct.h"
#include "data_tools/db/rocksdb/rocksdb_kv.h"

static constexpr uint64 DEFAULT_USER_COUNT = (1ull << 30);
static constexpr uint64 DEFAULT_BUCKET_CNT = (1ull << 10);
static constexpr const char* DEFAULT_DB_PATH = "./data";

// 简单的 key=value 参数解析
void parse_args(int argc, char** argv, uint64 &user_count, uint64 &bucket_cnt, std::string &db_path)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        auto pos = arg.find('=');
        if (pos == std::string::npos)
            continue; // 忽略不符合 key=value 的参数

        std::string key = arg.substr(0, pos);
        std::string value = arg.substr(pos + 1);

        if (key == "user_count")
        {
            user_count = std::stoull(value);
        }
        else if (key == "bucket_cnt")
        {
            bucket_cnt = std::stoull(value);
        }
        else if (key == "db_path")
        {
            db_path = value;
        }
        else
        {
            Logger::Warn("Unknown argument: " + key);
        }
    }
}

int main(int argc, char** argv)
{
    uint64 user_count  = DEFAULT_USER_COUNT;
    uint64 bucket_cnt  = DEFAULT_BUCKET_CNT;
    std::string db_path = DEFAULT_DB_PATH;

    parse_args(argc, argv, user_count, bucket_cnt, db_path);

    Logger::Info("user_count = " + std::to_string(user_count));
    Logger::Info("bucket_cnt = " + std::to_string(bucket_cnt));
    Logger::Info("db_path    = " + db_path);

    // 1. 生成数据
    std::vector<UserData> users;
    Logger::Info("Generating user data...");
    generate_users_data(users, user_count, /*seed=*/0);

    // 2. 分桶
    Logger::Info("Bucketizing data...");
    std::vector<std::vector<UserData>> buckets;
    bucketize_users_data(users, buckets, bucket_cnt);

    // 3. 打开 RocksDB
    Logger::Info("Opening RocksDB...");
    RocksDBKV db(db_path);

    // 4. 写入每个桶
    Logger::Info("Writing buckets...");
    for (uint64 b = 0; b < bucket_cnt; ++b)
    {
        if (!buckets[b].empty())
        {
            db.put_bucket(b, buckets[b]);
        }

        if ((b & 0x3F) == 0) // 每64桶打印一次
        {
            Logger::Info("Written bucket " + std::to_string(b) + "/" + std::to_string(bucket_cnt));
        }
    }

    Logger::Info("Done.");
    return 0;
}
