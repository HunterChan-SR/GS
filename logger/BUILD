load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "logger",
    srcs = ["logger.cpp"],
    hdrs = ["logger.h"],
    copts = ["-std=c++20"],
    deps = [
        "@googletest//:gtest",  # 如果要用PerformanceBenchmark
    ],
    visibility = ["//visibility:public"],
)
