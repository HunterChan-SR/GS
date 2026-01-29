load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "rocksdb_kv",
    srcs = ["rocksdb_kv.cpp"],
    hdrs = ["rocksdb_kv.h"],
    copts = [
        "-std=c++20",
        "-I/usr/local/include",   
    ],
    linkopts = [
        "-L/usr/local/lib",
        "-lrocksdb",
    ],
    deps = [
        "//data_tools/data_struct:data_struct",
    ],
    visibility = ["//visibility:public"],
)
