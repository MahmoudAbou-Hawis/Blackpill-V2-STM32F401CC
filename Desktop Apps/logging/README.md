**introduction:**

logging system for your C applications. It allows you to record and track program execution, events, and messages at different severity levels to various output channels.

**Key Features:**

- **Multiple Log Levels:** Define message severity with `LogLevel` enumeration (e.g., `LOG_DEBUG`, `LOG_INFO`, `LOG_WARNING`, `LOG_ERROR`, `LOG_CRITICAL`).
- **Flexible Output Channels:** Choose where to send messages with `LogChannels` (e.g., `LOG_OUT_FILE`, `LOG_OUT_CONSOLE`, `LOG_OUT_CONSOLE_FILE`).
- **Formatted Logging:** Use format strings and variable arguments in `log_write` for dynamic message construction.
- **Severity Threshold:** Set a minimum level with `log_setSeverity` to only log messages with higher levels.
- **Simplified Logging with Date & Time:** The `log_message` function logs a message with a specified severity level, format string, and **automatically includes the current date and time** for each entry, providing valuable context for your logs.
- **Clear and Detailed Comments:** Each function and enumeration is well-commented for easy understanding.

**Example Usage:**

```C
#include "logging.h"

void main(void)
{
    // Configure logging to both console and file
    log_setOutputChl(LOG_OUT_CONSOLE_FILE);
    
    log_fileCfg("myapp.log");

    // Set minimum log level to LOG_DEBUG
    log_setSeverity(LOG_DEBUG);

    // Debug message (won't be displayed due to set severity)
    log_write("Debug message: %d\n", 10);

    // Info message (displayed in console and file)
    log_message(LOG_INFO, "Application started successfully.");

}
```

**Functions:**

- `log_setOutputChl(LogChannels channel)`: Sets the output channel.
- `log_fileCfg(char * path)`: Specifies the log file path.
- `log_write(char * placeholders, ...)`: Writes a formatted message.
- `log_message(LogLevel level, char * msg)`: Logs a message with specified level.
- `log_setSeverity(LogLevel level)`: Sets the minimum log level.

**How to Use:**

1. Include `logging.h` in your code.
2. Configure log channels and file path using `log_setOutputChl` and `log_fileCfg`.
3. Use `log_write` or `log_message` to log messages with desired severity and format.
4. Adjust the minimum severity level with `log_setSeverity`.