#include <gtest/gtest.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" 
#include <chrono>
#include <sstream>
#include <iomanip>


int main(int argc, char **argv) {
    //Logger setup
    try
    {    
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::ostringstream filename;
        filename << "../logs/logs_" << std::put_time(std::localtime(&time), "%Y-%m-%d_%H-%M-%S") << ".txt";
        auto file_logger = spdlog::basic_logger_mt("file_log", filename.str());
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