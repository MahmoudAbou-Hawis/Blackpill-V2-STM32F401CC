/**
 *@brief Defines different log message severity levels.
 */
typedef enum 
{
    /**
     *@brief Debug level for detailed debugging information.
     */
    LOG_DEBUG,
    /**
     *@brief Info level for general informational messages.
     */
    LOG_INFO,
    /**
     *@brief Warning level for potential issues or important events.
     */
    LOG_WARNING,
    /**
     *@brief Error level for errors that require attention.
     */
    LOG_ERROR,
    /**
     *@brief Critical level for severe errors that might impact system integrity.
     */
    LOG_CRITICAL
} LogLevel;


/**
 *@brief Defines different channels for log output.
 */
typedef enum
{
    /**
     *@brief Sends log messages to a file.
     */
    LOG_OUT_FILE,
    /**
     *@brief Prints log messages to the console (terminal).
     */
    LOG_OUT_CONSOLE,
    /**
     *@brief Sends messages to both file and console.
     */
    LOG_OUT_CONSOLE_FILE
} LogChannels;


/**
 * @brief Sets the output channel for log messages.
 * @param[in] channel The desired output channel (LOG_OUT_FILE, LOG_OUT_CONSOLE, or LOG_OUT_CONSOLE_FILE).
 */
void log_setOutputChl(LogChannels channel);

/**
 * Specifies the file path where log messages should be written when using file-based output.
 * @param[in] path The path to the log file.
 */
void log_fileCfg(char * path);

/**
 * The primary function for logging messages.
 * @param[in] placeholders A format string containing placeholders for variable arguments.
 * @param ... Variable arguments to fill the placeholders in the format string.
 */
void log_write(char * placeholders, ...);

/**
 * Logs a message with a specified level and format string.
 * @param[in] level The severity level of the message (LOG_DEBUG, LOG_INFO, etc.).
 * @param[in] msg The message to be logged (format string).
 */
void log_message(LogLevel level, char * msg);

/**
 * Sets a minimum log level threshold. Messages with levels below this threshold won't be logged.
 * @param[in] level The minimum severity level to log.
 */
void log_setSeverity(LogLevel level);