#include "logging.h"
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define assert(condition) if (!condition) { \
  printf("Error in File: %s, Line: %d, Condition failed: %s\n", __FILE__, __LINE__, #condition); \
  exit(0); \
}

static LogLevel severity = LOG_DEBUG;
static LogChannels chl = LOG_OUT_CONSOLE ;
static char* logPath = NULL;


void log_setOutputChl(LogChannels channel)
{
    assert((channel == LOG_OUT_FILE|| channel == LOG_OUT_CONSOLE || channel == LOG_OUT_CONSOLE_FILE));
    chl = channel;
}



void log_write(char * placeholders, ...)
{
    assert(placeholders != NULL);
    va_list args;
    va_start(args, placeholders); 
    if(chl == LOG_OUT_CONSOLE)
    {
        vprintf(placeholders, args); 
    }
    else if(chl == LOG_OUT_CONSOLE_FILE)
    {
        assert(logPath != NULL);
        FILE *logfile = fopen(logPath, "a");
        vprintf(placeholders, args);
        vfprintf(logfile, placeholders, args);
        fclose(logfile);
    }
    else
    {
        assert(logPath != NULL);
        FILE *logfile = fopen(logPath, "a");
        vfprintf(logfile, placeholders, args);
        fclose(logfile);
    }
    va_end(args); 
}

void log_message(LogLevel level,char * msg)
{
    assert((level >= LOG_DEBUG && level <= LOG_CRITICAL && msg != NULL));
    if(level >= severity)
    {
        time_t current_time;
        time(&current_time);
        struct tm *time_info = localtime(&current_time);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);
        if(chl == LOG_OUT_CONSOLE)
        {
            printf("[%s] %s\n", timestamp, msg);
        }
        else if(chl ==  LOG_OUT_FILE)
        {
            assert(logPath != NULL);
            FILE *logfile = fopen(logPath, "a");
            fprintf(logfile,"[%s] %s\n", timestamp, msg);
            fclose(logfile);
        }
        else
        {
            assert(logPath != NULL);
            FILE *logfile = fopen(logPath, "a");
            fprintf(logfile,"[%s] %s\n", timestamp, msg);
            printf("[%s] %s\n", timestamp, msg);
            fclose(logfile);
        }
    }
    else
    {
        // No thing.
    }
}

void log_setSeverity(LogLevel level)
{
    assert((level >= LOG_DEBUG && level <= LOG_CRITICAL));
    severity = level;
}

void log_fileCfg(char * filepath)
{
    assert(filepath != NULL);
    assert((access(filepath, F_OK) != -1));
    logPath = filepath;
}