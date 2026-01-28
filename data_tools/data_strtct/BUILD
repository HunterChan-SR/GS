load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "data_struct",
    srcs = ["data_struct.cpp"],
    hdrs = ["data_struct.h"],
    visibility = ["//visibility:public"],
    copts = ["-std=c++20"],
    deps = [
        "//logger:logger",
    ],
)
