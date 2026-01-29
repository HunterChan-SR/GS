#include "data_tools/db/rocksdb/rocksdb_kv.h"
#include "bst.h"

BST<UserData<uint64,uint64>> build_bst_from_users_db(const std::string db_path, uint64 bucket_id)
{
    RocksDBKV kv(db_path);
    std::vector<UserData<uint64,uint64>> users = kv.scan_bucket(bucket_id);
    // kv.~RocksDBKV();
    return BST<UserData<uint64,uint64>>::build_tree(users);
}