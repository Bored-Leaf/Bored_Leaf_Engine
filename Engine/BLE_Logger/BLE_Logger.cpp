#include <print>
#include <fstream>
#include <filesystem>
#include <array>
#include <string_view>
#include <format>
#include <chrono>

#include "BLE_Logger.h"

// Temp solution to quick access functions for logging.
// TODO: Make a more appropriate design for a logger
// NEXT: Start doxygen
namespace ble::logger {
    namespace {
        constexpr std::string_view grey_text{"\033[38;5;8m"};
        constexpr std::string_view yellow_text{"\033[38;5;220m"};
        constexpr std::string_view orange_text{"\033[38;5;208m"};
        constexpr std::string_view red_text{"\033[38;5;196m"};
        constexpr std::string_view normal_text{"\033[0m"};

        constexpr std::array<std::string_view, static_cast<size_t>(Level::Count)> textColours{grey_text,
                                                                                              yellow_text,
                                                                                              orange_text,
                                                                                              red_text};

        constexpr std::array<std::string_view, static_cast<size_t>(Level::Count)> tag{"[STATUS]",
                                                                                      "[WARN]",
                                                                                      "[Error]",
                                                                                      "[FATAL]"};

        std::string_view getStatusTag(Level level) {
            return tag[static_cast<int>(level)];
        }

        std::string_view getStatusTagColour(Level level) {
            return textColours[static_cast<int>(level)];
        }

        // will be fixed for more appropriate design for a logger so ignore for now
        std::ofstream logFile;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

        std::string getLogFileName() {
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);
            std::tm tm{};
            localtime_r(&t, &tm);

            std::array<char, 32> buf{};
            std::strftime(buf.data(), buf.size(), "%Y-%m-%d_%Hh-%Mm-%Ss", &tm);

            return buf.data();
        }

        void setupLogFile() {
            std::filesystem::path logsDir{"logs"};

            if (!std::filesystem::exists(logsDir)) {
                if (std::filesystem::create_directory(logsDir)) {
                    log(Level::Status, "logs directory created in " + std::filesystem::current_path().string());
                } else {
                    log(Level::Warning, "logs directory couldn't be created!");
                }
            } else {
                log(Level::Status, "log directory already exists in " + std::filesystem::current_path().string());
            }

            std::string logFileName{getLogFileName() + ".log"};
            
            std::filesystem::path logFilePath{logsDir / logFileName};
            logFile = std::ofstream(logFilePath, std::ios::out);
        }
    }

    void log(Level level, const std::string &message) {
        print(level, message);
        write(level, message);
    }

    void print(Level level, const std::string &message) {
        std::println("{}{:<8} >>{} {}", getStatusTagColour(level), getStatusTag(level), normal_text, message);
    }

    void write(Level level, const std::string &message) {
        if (logFile.is_open()) {
            std::string finalMessage{std::format("{:<8} >> {}\n", getStatusTag(level), message)};
            logFile.write(finalMessage.data(), finalMessage.size());
        }
    }

    void init() {
        setupLogFile();
        log(Level::Status, "Logger initialised");
    }

    void shutdown() {
        log(Level::Status, "Logger shutdown");
        logFile.close();
    }
}