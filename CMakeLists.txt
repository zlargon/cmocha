cmake_minimum_required(VERSION 3.0)

project(
    mocha                   # project name
    VERSION 1.0.0           # project version
    LANGUAGES C CXX         # programming languages
)

# create a target 'mocha' as a library
add_library(
    mocha                   # target name
    mocha.c                 # source files
)

# add header to target 'mocha'
target_include_directories(
    mocha                   # target name
    PUBLIC .                # header directory path (mocha.h)
)
