#ifndef PARTY_H
#define PARTY_H

#include <string>
#include <vector>
#include "data_tools/data_struct/data_struct.h"
#include "crypto/crypto.h"

class Alice
{
private:
    std::string name;
};

class Bob
{
private:
    std::string name;
    std::string db_path;
    PrimeFieldNumber<uint64> MSK;
    std::vector<UserData<PrimeFieldNumber<uint64>, PrimeFieldNumber<uint64>>> users_data;
    std::vector<PrimeFieldNumber<uint64>> full_binary_tree;
    std::vector<PrimeFieldNumber<uint64>> level_beta;

public:
    Bob(const std::string &name, const std::string &db_path, uint64 prime_modulus)
        : name(name), db_path(db_path), MSK(prime_modulus) {}
    Bob(const std::string &db_path, uint64 prime_modulus)
        : name("Bob"), db_path(db_path), MSK(prime_modulus) {}

    /**
     * 加载并加密用户数据
     * @param pucket_id 桶ID
     */
    void load_and_encrypt_users_data(uint64 pucket_id);

    /**
     * 构建满二叉树
     */
    void build_full_binary_tree();
};

#endif // PARTY_H