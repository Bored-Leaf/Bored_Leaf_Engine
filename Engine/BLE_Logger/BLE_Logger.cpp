#include <print>
#include <fstream>
#include <filesystem>
#include <array>
#include <string_view>

#include "BLE_Logger.h"

// Temp solution to quick access functions for logging.
// TODO: Make a more appropriate design for a logger
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

        constexpr std::array<std::string, static_cast<size_t>(Level::Count)> tag{"[STATUS]",
                                                                                 "[WARN]",
                                                                                 "[Error]",
                                                                                 "[FATAL]"};

        std::string getTerminalTag(Level level) {
            return  std::string(textColours[static_cast<int>(level)]) + tag[static_cast<int>(level)] + std::string(normal_text);
        }

        const char* getFileTag(Level level) {
            return tag[static_cast<int>(level)].data();
        }

        // will be fixed for more appropriate design for a logger so ignore for now
        std::ofstream logFile;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

        void setupLogFile() {
            std::filesystem::path logs{"logs"};

            if (!std::filesystem::exists(logs)) {
                if (std::filesystem::create_directory(logs)) {
                    log(Level::Status, "logs directory created in " + std::filesystem::current_path().string());
                } else {
                    log(Level::Status, "logs directory couldn't be created!");
                }
            } else {
                log(Level::Status, "log directory already exists in " + std::filesystem::current_path().string());
            }

            std::filesystem::path logPath{logs / "logFile"};
            logFile = std::ofstream(logPath, std::ios::out);
        }
    }

    void log(Level level, const std::string &message) {
        print(level, message);
        write(level, message);
    }

    // NEXT: Format with left aligned
    void print(Level level, const std::string &message) {
        std::println("{} {}", getTerminalTag(level), message);
    }

    // NEXT: use println instead of logFile directly, format with left aligned
    void write(Level level, const std::string &message) {
        if (logFile.is_open()) {
            std::string statusTag{getFileTag(level)};
            std::string finalMessage{statusTag + " " + message + '\n'};
            logFile.write(finalMessage.data(), finalMessage.size());
        }
    }

    void init() {
        log(Level::Status, "Status test");
        log(Level::Warning, "Warning test");
        log(Level::Error, "Error test");
        log(Level::Fatal, "Fatal test");
        setupLogFile();
        log(Level::Status, "Logger initialised");
    }

    void shutdown() {
        logFile.close();
        log(Level::Status, "Logger shutdown");
    }
}