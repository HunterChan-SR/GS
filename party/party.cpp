#include "party.h"
#include "data_tools/db/rocksdb/rocksdb_kv.h"
#include "bst/bst.h"
#include <vector>

Alice::Alice(const std::string &name, const PrimeFieldNumber<uint64> &alpha) : name(name), alpha(alpha) {}

Alice::Alice(const PrimeFieldNumber<uint64> &alpha) : name("Alice"), alpha(alpha) {}

void Alice::get_leaves_data_and_beta_minus_k(std::pair<std::vector<PrimeFieldNumber<uint64>>, std::vector<PrimeFieldNumber<uint64>>> leaves_data_and_beta_minus_k)
{
    leaves_data = leaves_data_and_beta_minus_k.first;
    beta_minus_k = leaves_data_and_beta_minus_k.second;
}

PrimeFieldNumber<uint64> Alice::cal_ea(size_t i)
{
    PrimeFieldNumber<uint64> da = alpha - beta_minus_k[i];
    PrimeFieldNumber<uint64> r = PrimeFieldNumber<uint64>::random(alpha.get_modulus());
    return da + r;
}

Bob::Bob(const std::string &name, const std::string &db_path, uint64 prime_modulus)
    : name(name), db_path(db_path), MSK(PrimeFieldNumber<uint64>::random(prime_modulus)) {}
Bob::Bob(const std::string &db_path, uint64 prime_modulus)
    : name("Bob"), db_path(db_path), MSK(PrimeFieldNumber<uint64>::random(prime_modulus)) {}

void Bob::load_and_encrypt_users_data(uint64 pucket_id)
{
    RocksDBKV kv(db_path);
    std::vector<UserData<uint64, uint64>> users = kv.scan_bucket(pucket_id);
    leaves_id.clear();
    leaves_data.clear();
    for (auto &user : users)
    {
        leaves_id.push_back(PrimeFieldNumber<uint64>(user.id, MSK.get_modulus()));

        PrimeFieldNumber<uint64> data(user.data, MSK.get_modulus());
        data = data.pow((MSK + leaves_id.back()).mod_inverse());
        leaves_data.push_back(data);
    }
    kv.~RocksDBKV();
}

void Bob::build_full_binary_tree()
{
    auto full_binary_tree = BST<PrimeFieldNumber<uint64>>::build_full_tree_as_leaves(leaves_id, PrimeFieldNumber<uint64>(MSK.get_modulus() - 1, MSK.get_modulus()));
    beta.clear();
    beta = full_binary_tree.get_level_order_nodes();
}

std::pair<std::vector<PrimeFieldNumber<uint64>>, std::vector<PrimeFieldNumber<uint64>>> Bob::compute_level_k_and_send_to_alice()
{

    level_k.clear();
    // beta  - k
    std::vector<PrimeFieldNumber<uint64>> beta_minus_k;
    for (size_t i = 1, k = 1; i <= beta.size(); i *= 2, k += i)
    {
        level_k.push_back(PrimeFieldNumber<uint64>::random(MSK.get_modulus()));
        for (size_t j = k / 2; j < k; j++)
        {
            beta_minus_k.push_back(beta[j] - level_k.back());
        }
    }
    return {leaves_data, beta_minus_k};
}
