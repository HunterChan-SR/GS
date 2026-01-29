load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "bst",
    srcs = ["bst.cpp"],
    hdrs = ["bst.h"],
    copts = ["-std=c++20"],
    visibility = ["//visibility:public"],
    deps = [
        "//data_tools/data_struct:data_struct",
        "//logger",
        "//data_tools/db/rocksdb:rocksdb_kv",
    ],
)

cc_binary(
    name = "bst_example",
    srcs = ["bst_example.cpp"],
    copts = [
        "-std=c++20",
    ],
    deps = [
        ":bst",
        "//data_tools/data_generater",
        "//data_tools/data_struct:data_struct",
        "//logger",
        "//data_tools/db/rocksdb:rocksdb_kv",
    ],
)
