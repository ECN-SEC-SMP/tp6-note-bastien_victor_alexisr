#include <gtest/gtest.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" 


int main(int argc, char **argv) {
    //Logger setup
    try
    {    
        auto file_logger = spdlog::basic_logger_mt("file_log", "../test/logs.txt");
        file_logger->flush_on(spdlog::level::debug);
        spdlog::set_default_logger(file_logger);
        spdlog::set_level(spdlog::level::debug);
        spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }

    //Test setup
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::GTEST_FLAG(filter) = "Deck.Shuffle";
    //::testing::GTEST_FLAG(repeat) = 100; 
    ::testing::GTEST_FLAG(break_on_failure) = true;
    return RUN_ALL_TESTS();
}