#include "data_generater.h"
#include <random>


uint64 random_uint64(){
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64> dis(0, UINT64_MAX);
    return dis(gen);
}

void generate_users_data(std::vector<UserData<uint64,uint64>> &users, size_t size, uint64 seed)
{
    users.resize(size);
    std::mt19937_64 gen;

    if (seed == 0)
    {
        std::random_device rd;
        gen.seed(rd());
    }
    else
    {
        gen.seed(seed);
    }

    std::uniform_int_distribution<uint64> dis(1, UINT64_MAX);

    for (size_t i = 0; i < size; ++i)
    {
        UserData<uint64, uint64> user;
        user.id = static_cast<uint64>(i + 1);
        user.data = dis(gen);
        users[i] = user;
    }
}

void generate_users_data_range(std::vector<UserData<uint64,uint64>> &users, size_t size,
                               uint64 data_min, uint64 data_max, uint64 seed)
{
    users.resize(size);
    std::mt19937_64 gen;

    if (seed == 0)
    {
        std::random_device rd;
        gen.seed(rd());
    }
    else
    {
        gen.seed(seed);
    }

    std::uniform_int_distribution<uint64> dis(data_min, data_max);

    for (size_t i = 0; i < size; ++i)
    {
        UserData<uint64, uint64> user;
        user.id = static_cast<uint64>(i + 1);
        user.data = dis(gen);
        users[i] = user;
    }
}

void bucketize_users_data(const std::vector<UserData<uint64,uint64>> &users,
                          std::vector<std::vector<UserData<uint64,uint64>>> &buckets,
                          size_t bucket_count)
{
    buckets.clear();
    buckets.resize(bucket_count);

    for (const auto &user : users)
    {
        size_t bucket_index = user.id % bucket_count;
        buckets[bucket_index].push_back(user);
    }
}