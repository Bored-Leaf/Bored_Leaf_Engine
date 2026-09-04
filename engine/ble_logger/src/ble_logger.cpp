#include <print>
#include <fstream>
#include <filesystem>
#include <array>
#include <string_view>
#include <format>
#include <chrono>

#include "ble_logger.hpp"

/**
 * @file BLE_Logger.cpp.
 * @brief Internal logging implementation details.
 */

namespace ble::logger {
    namespace {
        /** @internal */
        constexpr std::string_view grey_text{"\033[38;5;8m"};       ///< Used for [STATUS] tag colour.

        /** @internal */
        constexpr std::string_view yellow_text{"\033[38;5;220m"};   ///< Used for [WARN] tag colour.

        /** @internal */
        constexpr std::string_view orange_text{"\033[38;5;208m"};   ///< Used for [ERROR] tag colour.

        /** @internal */
        constexpr std::string_view red_text{"\033[38;5;196m"};      ///< Used for [FATAL] tag colour.

        /** @internal */
        constexpr std::string_view normal_text{"\033[0m"};          ///< Used for returning terminal colour to default.

        /** 
         * @internal 
         * @brief Vector of textColours for indexing.
         */
        constexpr std::array<std::string_view, static_cast<size_t>(Level::Count)> textColours{grey_text,
                                                                                              yellow_text,
                                                                                              orange_text,
                                                                                              red_text};

        /**
         * @internal
         * @brief Vector of tag strings for indexing.
         */
        constexpr std::array<std::string_view, static_cast<size_t>(Level::Count)> tagString{"[STATUS]",
                                                                                            "[WARN]",
                                                                                            "[Error]",
                                                                                            "[FATAL]"};

        /**
         * @internal
         * @brief Get the log category tag string.
         * @note Uses @ref tagString for indexing.
         * 
         * @param level The category of the log.
         * @return A std::string_view of the log category text.
         */
        std::string_view getStatusTag(Level level) {
            return tagString[static_cast<int>(level)];
        }

        /**
         * @internal
         * @brief Get the log category tag colour.
         * @details Gets the terminal foreground colour for the corresponding log category.
         * @note Uses @ref textColours for indexing.
         * 
         * @param level The category of the log.
         * @return A std::string_view of the log category colour ANSI escape code.
         */
        std::string_view getTagColour(Level level) {
            return textColours[static_cast<int>(level)];
        }

        /**
         * @internal
         * @brief File object logs are written to.
         *
         * @note File is only visible in source file.
         */
        std::ofstream logFile;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

        /**
         * @internal
         * @brief Creates a log file name containing the year, month, day, hours, minutes and seconds
         * with the following format: yyyy-mm-dd_hh-mm-ss format.
         * 
         * @return A std::string of the log file name.
         */
        std::string getLogFileName() {
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);
            std::tm tm{};
            localtime_r(&t, &tm);

            std::array<char, 32> buf{};
            std::strftime(buf.data(), buf.size(), "%Y-%m-%d_%Hh-%Mm-%Ss", &tm);

            return buf.data();
        }

        /**
         * @internal
         * @brief Creates a log file to write logs to.
         * 
         * @note If directory cannot be created then it prints a Warning to terminal only
         * and the log file will not be created.
         */
        void setupLogFile() {
            std::filesystem::path logsDir{"logs"};

            if (!std::filesystem::exists(logsDir)) {
                if (std::filesystem::create_directory(logsDir)) {
                    log(Level::Status, "logs directory created in " + std::filesystem::current_path().string());
                } else {
                    log(Level::Warning, "logs directory couldn't be created!");
                    return;
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
        if (level >= Level::Count) {
            log(Level::Warning, "Cannot pass Level::Count to log(), Level::Count is only used internally!");
            return;
        }
        print(level, message);
        write(level, message);
    }

    void print(Level level, const std::string &message) {
        std::println("{}{:<8} >>{} {}", getTagColour(level), getStatusTag(level), normal_text, message);
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
        log(Level::Count, "test");
    }

    void shutdown() {
        log(Level::Status, "Logger shutdown");
        logFile.close();
    }
}