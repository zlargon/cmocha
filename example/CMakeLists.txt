cmake_minimum_required(VERSION 3.0)

# include mocha library (target: mocha)
add_subdirectory(
    ..                  # the relative path to mocha's CMakeLists.txt (../)
    mocha               # the directrory to build the mocha (example/build/mocha/)
    EXCLUDE_FROM_ALL    # only build needed targets
)

add_executable(
    example             # target name
    example.c           # source files
)

target_link_libraries(
    example             # target name
    mocha               # mocha library (from mocha target)
)
