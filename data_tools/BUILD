load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "user_data_init",
    srcs = ["user_data_init.cpp"],
    copts = ["-std=c++20"],
    deps = [
        "//data_tools/data_generater:data_generater",
        "//data_tools/data_strtct:data_struct",
        "//data_tools/db/rocksdb:rocksdb_kv",
        "//logger:logger",
    ],
    visibility = ["//visibility:public"],
)
