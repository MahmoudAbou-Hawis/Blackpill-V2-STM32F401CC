#include "logging.h"

int main(void)
{
    log_fileCfg("./log.txt");
    log_setOutputChl(LOG_OUT_CONSOLE_FILE);
    log_setSeverity(LOG_WARNING);
    log_write("%s %d\n","I'am here",10);
    log_message(LOG_DEBUG, "This is a debug message");
    log_message(LOG_INFO, "This is an informational message");
    log_message(LOG_WARNING, "This is a warning message");
    log_message(LOG_ERROR, "This is an error message");
    log_message(LOG_CRITICAL, "This is a critical message");
    return 0;
}