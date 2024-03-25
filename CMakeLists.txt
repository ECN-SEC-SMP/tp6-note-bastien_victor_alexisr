cmake_minimum_required(VERSION 3.5)
project(Monopoly)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${GTest_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES "sources/*.cc" "sources/*.h")
file(GLOB_RECURSE TESTS "test/*.cc")

add_executable(
    Tests 
    ${SOURCES}
    ${TESTS}
)

add_executable(
    Main 
    ${SOURCES}
    main.cpp
)

target_link_libraries(
    Tests
    GTest::gtest_main
) 