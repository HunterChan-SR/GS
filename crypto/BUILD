load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "crypto",
    srcs = ["crypto.cpp"],
    hdrs = ["crypto.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//logger:logger",
        "//data_tools/data_struct:data_struct",
        "//data_tools/data_generater:data_generater",
    ],
)