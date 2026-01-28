load("@rules_cc//cc:cc_test.bzl", "cc_test")
load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "data_generater",
    srcs = ["data_generater.cpp"],
    hdrs = ["data_generater.h"],
    visibility = ["//visibility:public"],
    copts = ["-std=c++20"],
    deps = [
        "//data_tools/data_strtct:data_struct",
    ],
)


cc_test(
    name = "data_generater_benchmark",
    srcs = ["data_generater_benchmark.cpp"],
    deps = [
        ":data_generater",
        "@googletest//:gtest_main",
        "//logger:logger",
    ],
    copts = ["-std=c++20"],
    timeout = "long",
)