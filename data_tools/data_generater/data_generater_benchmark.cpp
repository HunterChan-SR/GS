#ifndef USE_GTEST
#define USE_GTEST
#include "data_generater.h"
#include "logger/logger.h"
#include <chrono>
#include <iostream>
#include <iomanip>


TEST_F(PerformanceBenchmark, Generate1Million) {
    std::vector<UserData> users;
    auto start = std::chrono::high_resolution_clock::now();
    generate_users_data(users, 1000000);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    PrintBenchmarkResult("Generate 1 Million Records", 1000000, duration);
    EXPECT_EQ(users.size(), 1000000);
}

TEST_F(PerformanceBenchmark, Generate10Million) {
    std::vector<UserData> users;
    auto start = std::chrono::high_resolution_clock::now();
    generate_users_data(users, 10000000);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    PrintBenchmarkResult("Generate 10 Million Records", 10000000, duration);
    EXPECT_EQ(users.size(), 10000000);
}

TEST_F(PerformanceBenchmark, Generate100Million) {
    std::vector<UserData> users;
    auto start = std::chrono::high_resolution_clock::now();
    generate_users_data(users, 100000000);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    PrintBenchmarkResult("Generate 100 Million Records", 100000000, duration);
    EXPECT_EQ(users.size(), 100000000);
}

TEST_F(PerformanceBenchmark, Generate1Billion) {
    std::vector<UserData> users;
    auto start = std::chrono::high_resolution_clock::now();
    generate_users_data(users, 1000000000);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    PrintBenchmarkResult("Generate 1 Billion Records", 1000000000, duration);
    EXPECT_EQ(users.size(), 1000000000);
}

TEST_F(PerformanceBenchmark, GenerateWithRange) {
    std::vector<UserData> users;
    auto start = std::chrono::high_resolution_clock::now();
    generate_users_data_range(users, 1000000, 1000, 100000);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    PrintBenchmarkResult("Generate 1 Million Records (with range)", 1000000, duration);
    
    for (const auto& user : users) {
        EXPECT_GE(user.data, 1000);
        EXPECT_LE(user.data, 100000);
    }
}

TEST_F(PerformanceBenchmark, Bucketize1Million) {
    std::vector<UserData> users;
    generate_users_data(users, 1000000);
    
    std::vector<std::vector<UserData>> buckets;
    auto start = std::chrono::high_resolution_clock::now();
    bucketize_users_data(users, buckets, 128);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    PrintBenchmarkResult("Bucketize 1 Million Records (128 buckets)", 1000000, duration);
    
    // Verify all records are distributed
    size_t total = 0;
    for (const auto& bucket : buckets) {
        total += bucket.size();
    }
    EXPECT_EQ(total, 1000000);
}

TEST_F(PerformanceBenchmark, Bucketize10Million) {
    std::vector<UserData> users;
    generate_users_data(users, 10000000);
    
    std::vector<std::vector<UserData>> buckets;
    auto start = std::chrono::high_resolution_clock::now();
    bucketize_users_data(users, buckets, 256);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    PrintBenchmarkResult("Bucketize 10 Million Records (256 buckets)", 10000000, duration);
    
    // Verify all records are distributed
    size_t total = 0;
    for (const auto& bucket : buckets) {
        total += bucket.size();
    }
    EXPECT_EQ(total, 10000000);
}

TEST_F(PerformanceBenchmark, Bucketize100Million) {
    std::vector<UserData> users;
    generate_users_data(users, 100000000);
    
    std::vector<std::vector<UserData>> buckets;
    auto start = std::chrono::high_resolution_clock::now();
    bucketize_users_data(users, buckets, 512);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    PrintBenchmarkResult("Bucketize 100 Million Records (512 buckets)", 100000000, duration);
    
    // Verify all records are distributed
    size_t total = 0;
    for (const auto& bucket : buckets) {
        total += bucket.size();
    }
    EXPECT_EQ(total, 100000000);
}

TEST_F(PerformanceBenchmark, Bucketize1Billion) {
    std::vector<UserData> users;
    generate_users_data(users, 1000000000);
    
    std::vector<std::vector<UserData>> buckets;
    auto start = std::chrono::high_resolution_clock::now();
    bucketize_users_data(users, buckets, 1024);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    PrintBenchmarkResult("Bucketize 1 Billion Records (1024 buckets)", 1000000000, duration);
    
    // Verify all records are distributed
    size_t total = 0;
    for (const auto& bucket : buckets) {
        total += bucket.size();
    }
    EXPECT_EQ(total, 1000000000);
}

// Correctness Tests
class CorrectnessTest : public ::testing::Test {
protected:
    void PrintTestResult(const std::string& test_name, bool passed) {
        std::cout << "\n" << test_name << ": " 
                  << (passed ? "✓ PASSED" : "✗ FAILED") << "\n";
    }
};

TEST_F(CorrectnessTest, GenerateDataIDSequence) {
    // 验证ID是否连续递增
    std::vector<UserData> users;
    size_t test_size = 10000;
    generate_users_data(users, test_size);
    
    bool passed = true;
    for (size_t i = 0; i < test_size; ++i) {
        if (users[i].id != i + 1) {
            passed = false;
            break;
        }
    }
    
    PrintTestResult("ID Sequence Check (10K records)", passed);
    EXPECT_TRUE(passed);
}

TEST_F(CorrectnessTest, GenerateDataNonZero) {
    // 验证生成的数据都非零
    std::vector<UserData> users;
    size_t test_size = 100000;
    generate_users_data(users, test_size, 12345);  // 使用固定种子保证可重复
    
    bool has_zero = false;
    for (const auto& user : users) {
        if (user.data == 0) {
            has_zero = true;
            break;
        }
    }
    
    PrintTestResult("Non-Zero Data Check (100K records)", !has_zero);
    EXPECT_FALSE(has_zero);
}

TEST_F(CorrectnessTest, GenerateRangeDataBounds) {
    // 验证范围生成的数据是否都在指定范围内
    std::vector<UserData> users;
    size_t test_size = 100000;
    uint64 data_min = 5000;
    uint64 data_max = 50000;
    
    generate_users_data_range(users, test_size, data_min, data_max, 54321);
    
    bool all_in_range = true;
    for (const auto& user : users) {
        if (user.data < data_min || user.data > data_max) {
            all_in_range = false;
            break;
        }
    }
    
    PrintTestResult("Range Bounds Check (100K records)", all_in_range);
    EXPECT_TRUE(all_in_range);
}

TEST_F(CorrectnessTest, BucketizeAllRecordsIncluded) {
    // 验证分桶后所有记录都被包含
    std::vector<UserData> users;
    size_t test_size = 100000;
    size_t bucket_count = 64;
    
    generate_users_data(users, test_size);
    std::vector<std::vector<UserData>> buckets;
    bucketize_users_data(users, buckets, bucket_count);
    
    size_t total = 0;
    for (const auto& bucket : buckets) {
        total += bucket.size();
    }
    
    PrintTestResult("All Records Included in Buckets (100K)", total == test_size);
    EXPECT_EQ(total, test_size);
}

TEST_F(CorrectnessTest, BucketizeCorrectDistribution) {
    // 验证分桶逻辑是否正确（ID % bucket_count == bucket_index）
    std::vector<UserData> users;
    size_t test_size = 10000;
    size_t bucket_count = 128;
    
    generate_users_data(users, test_size);
    std::vector<std::vector<UserData>> buckets;
    bucketize_users_data(users, buckets, bucket_count);
    
    bool correct = true;
    for (size_t i = 0; i < bucket_count; ++i) {
        for (const auto& user : buckets[i]) {
            if (user.id % bucket_count != i) {
                correct = false;
                break;
            }
        }
        if (!correct) break;
    }
    
    PrintTestResult("Correct Bucket Distribution (10K)", correct);
    EXPECT_TRUE(correct);
}

TEST_F(CorrectnessTest, BucketizeNoBucketEmpty) {
    // 验证分桶后是否有空桶（对于足够大的数据集）
    std::vector<UserData> users;
    size_t test_size = 100000;
    size_t bucket_count = 64;
    
    generate_users_data(users, test_size);
    std::vector<std::vector<UserData>> buckets;
    bucketize_users_data(users, buckets, bucket_count);
    
    int empty_count = 0;
    for (const auto& bucket : buckets) {
        if (bucket.empty()) {
            empty_count++;
        }
    }
    
    // 对于足够大的数据集，应该没有空桶
    bool no_empty = (empty_count == 0);
    std::cout << "  Empty buckets: " << empty_count << " out of " << bucket_count << "\n";
    
    PrintTestResult("No Empty Buckets (100K, 64 buckets)", no_empty);
    EXPECT_EQ(empty_count, 0);
}

TEST_F(CorrectnessTest, SeedReproducibility) {
    // 验证相同种子生成相同数据
    std::vector<UserData> users1, users2;
    uint64 seed = 99999;
    size_t test_size = 10000;
    
    generate_users_data(users1, test_size, seed);
    generate_users_data(users2, test_size, seed);
    
    bool identical = true;
    for (size_t i = 0; i < test_size; ++i) {
        if (users1[i].id != users2[i].id || users1[i].data != users2[i].data) {
            identical = false;
            break;
        }
    }
    
    PrintTestResult("Seed Reproducibility (10K records)", identical);
    EXPECT_TRUE(identical);
}

#endif // USE_GTEST