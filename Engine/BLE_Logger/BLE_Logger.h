#pragma once

#include <string>

/**
 * @brief Logs to the terminal and a log file
 * @details A first iteration of a simple logger with free functions that can be called anywhere
 * Its simply logs to the terminal and a file with a category of the log and its corresponding
 * message.
 *
 * @todo end-developer able to call @ref log for their own game code.
 * @todo callbacks for end-developer defined custom logging behaviour inside the engine.
 */
namespace ble::logger {
    /**
     * @internal
     * @brief Sets up the log file.
     */
    void init();    

    /**
     * @internal
     * @brief Closes the log file.
     */
    void shutdown();

    /**
     * @internal
     * @brief The category of logs.
     * @details 4 different levels of categories a log can belong to.
     * Will find a way to get rid of Count in the future when updating the 
     * @ref logger implementation.
     *
     * @warning Count is strictly only used internally to get the number of 
     * elements in this enum class.
     */
    enum class Level : uint8_t {
        Status,     ///< General information.
        Warning,    ///< Potential mistakes or issues.
        Error,      ///< Errors that can cause UB or unintended side effects.
        Fatal,      ///< Strictly used when BLE crahes from a known cause.
        Count       ///< Strictly only used to get number of elements in Level.
    };

    /**
     * @internal
     * @brief Logs a message with a corresponding category tag.
     * @details calls @ref print and @ref write internally.
     *
     * @note Will log a warning log if @ref Level::Count is passed as level
     * without logging the original message.
     * 
     * @param level The category of the log.
     * @param message The contents of the log.
     */
    void log(Level level, const std::string &message);

    /**
     * @internal
     * @brief Prints a coloured tagged message to the terminal.
     * @details Prints the tag in a specific colour matching the category
     * while printing the message in the default terminal text colour.
     * 
     * @param level The category of the log.
     * @param message The contents of the log.
     */
    void print(Level level, const std::string &message);

    /**
     * @internal
     * @brief Writes a tagged message to a log file.
     * @note does nothing if the log file isn't open or successfully created
     * 
     * @param level The category of the log.
     * @param message The contents of the log.
     */
    void write(Level level, const std::string &message);
}