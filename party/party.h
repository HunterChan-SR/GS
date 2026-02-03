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
    PrimeFieldNumber<uint64> alpha;
    std::vector<PrimeFieldNumber<uint64>> leaves_data;
    std::vector<PrimeFieldNumber<uint64>> beta_minus_k;

public:
    Alice(const std::string &name, const PrimeFieldNumber<uint64> &alpha);
    Alice(const PrimeFieldNumber<uint64> &alpha);

    void get_leaves_data_and_beta_minus_k(std::pair<std::vector<PrimeFieldNumber<uint64>>, std::vector<PrimeFieldNumber<uint64>>> leaves_data_and_beta_minus_k);

    PrimeFieldNumber<uint64> cal_ea(size_t i);

};

class Bob
{
private:
    std::string name;
    std::string db_path;
    PrimeFieldNumber<uint64> MSK;

    std::vector<PrimeFieldNumber<uint64>> leaves_id;
    std::vector<PrimeFieldNumber<uint64>> leaves_data;

    std::vector<PrimeFieldNumber<uint64>> beta;
    std::vector<PrimeFieldNumber<uint64>> level_k;

public:
    Bob(const std::string &name, const std::string &db_path, uint64 prime_modulus);

    Bob(const std::string &db_path, uint64 prime_modulus);
    /**
     * 加载并加密用户数据
     * @param pucket_id 桶ID
     */
    void load_and_encrypt_users_data(uint64 pucket_id);

    /**
     * 构建满二叉树
     */
    void build_full_binary_tree();

    /**
     * 计算level_k并发送给Alice  users_data和beta-k
     */
    std::pair<std::vector<PrimeFieldNumber<uint64>>, std::vector<PrimeFieldNumber<uint64>>> compute_level_k_and_send_to_alice();

    
};

#endif // PARTY_H