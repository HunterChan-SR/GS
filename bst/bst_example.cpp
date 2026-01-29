#include <vector>
#include "data_tools/data_struct/data_struct.h"
#include "data_tools/data_generater/data_generater.h"
#include "bst.h"
#include "data_tools/db/rocksdb/rocksdb_kv.h"

/**
 * 生成用户数据并构建 BST，打印结果
 */
void t_generate_and_build_bst()
{
    std::vector<UserData<uint64,uint64>> users;
    generate_users_data(users, 32, 0);

    Logger::Info("Generated Users:");
    for (const auto &u : users)
    {
        u.log_info();
    }

    Logger::Info("Building BST...");
    BST<UserData<uint64,uint64>> tree = BST<UserData<uint64,uint64>>::build_tree(users);

    tree.log_tree_dfs();
    tree.log_tree_bfs();
}

/**
 * 从 RocksDB 数据库中指定 bucket 构建 BST 并打印
 */
void t_build_bst_from_db()
{
    std::vector<UserData<uint64,uint64>> users;
    generate_users_data(users, 32, 0);
    const std::string db_path = "./data";

    RocksDBKV kv(db_path);
    std::vector<std::vector<UserData<uint64,uint64>>> buckets;
    bucketize_users_data(users, buckets, 4);
    for (size_t i = 0; i < buckets.size(); ++i)
    {
        Logger::Info("Putting bucket " + std::to_string(i) + " to RocksDB, size = " + std::to_string(buckets[i].size()));
        kv.put_bucket(i, buckets[i]);
        for (const auto &u : buckets[i])
        {
            u.log_info();
        }
    }
    kv.~RocksDBKV(); // 关闭数据库

    const uint64 bucket_id = 0;
    Logger::Info("Building BST from RocksDB bucket " + std::to_string(bucket_id) + "...");
    BST<UserData<uint64,uint64>> tree = build_bst_from_users_db(db_path, bucket_id);

    tree.log_tree_dfs();
    tree.log_tree_bfs();
}

void t_build_bst_form_leaves()
{
    std::vector<int> items = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    Logger::Info("Building BST as leaves...");
    BST<int> tree = BST<int>::build_full_tree_as_leaves(items, 100);

    tree.log_tree_dfs();
    tree.log_tree_bfs();
}

int main()
{
    // t_generate_and_build_bst();
    // t_build_bst_from_db();
    t_build_bst_form_leaves();
    return 0;
}