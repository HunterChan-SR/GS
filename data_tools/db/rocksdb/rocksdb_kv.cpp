#include "rocksdb_kv.h"

#include <rocksdb/options.h>
#include <rocksdb/write_batch.h>
#include <rocksdb/iterator.h>

#include <cassert>
#include <cstring>
#include <endian.h>

namespace
{

    std::string encode_key_impl(uint64 bucket, uint64 id)
    {
        std::string key;
        key.resize(16);

        uint64 b = htobe64(bucket);
        uint64 i = htobe64(id);

        memcpy(&key[0], &b, 8);
        memcpy(&key[8], &i, 8);
        return key;
    }

} // anonymous namespace

RocksDBKV::RocksDBKV(const std::string &path) : db_(nullptr)
{
    rocksdb::Options options;
    options.create_if_missing = true;
    options.write_buffer_size = 512 << 20; // 512 MB

    auto s = rocksdb::DB::Open(options, path, &db_);
    assert(s.ok());
}

RocksDBKV::~RocksDBKV()
{
    delete db_;
}

std::string RocksDBKV::encode_key(uint64 bucket_id, uint64 user_id)
{
    return encode_key_impl(bucket_id, user_id);
}

void RocksDBKV::put_bucket(uint64 bucket_id,
                           const std::vector<UserData> &users)
{
    rocksdb::WriteBatch batch;

    for (const auto &u : users)
    {
        auto key = encode_key(bucket_id, u.id);
        rocksdb::Slice value(
            reinterpret_cast<const char *>(&u.data),
            sizeof(u.data));
        batch.Put(key, value);
    }

    auto s = db_->Write(rocksdb::WriteOptions(), &batch);
    assert(s.ok());
}

std::vector<UserData> RocksDBKV::scan_bucket(uint64 bucket_id)
{
    std::vector<UserData> result;

    std::string start = encode_key(bucket_id, 0);
    std::string end = encode_key(bucket_id + 1, 0);

    rocksdb::ReadOptions ro;
    ro.total_order_seek = true;

    std::unique_ptr<rocksdb::Iterator> it(db_->NewIterator(ro));

    for (it->Seek(start);
         it->Valid() && it->key().compare(end) < 0;
         it->Next())
    {

        UserData u;
        memcpy(&u.id, it->key().data() + 8, sizeof(u.id));
        u.id = be64toh(u.id);
        memcpy(&u.data, it->value().data(), sizeof(u.data));
        result.push_back(u);
    }

    return result;
}
