#include "data_tools/db/rocksdb/rocksdb_kv.h"
#include "bst.h"

BST<UserData> build_bst_from_users_db(const std::string db_path, uint64 bucket_id)
{
    RocksDBKV kv(db_path);
    std::vector<UserData> users = kv.scan_bucket(bucket_id);
    return BST<UserData>::build_tree(users);
}