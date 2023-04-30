#include "ignite/logging.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const char *
ignite_log_level_to_c_string(const enum ignite_log_level log_level) {
    switch (log_level) {
    case LOG_LEVEL_TRACE:
        return "TRACE";
    case LOG_LEVEL_DEBUG:
        return "DEBUG";
    case LOG_LEVEL_INFO:
        return "INFO";
    case LOG_LEVEL_WARN:
        return "WARN";
    case LOG_LEVEL_ERROR:
        return "ERROR";
    case LOG_LEVEL_CRIT:
        return "CRIT";
    default:
        return "NONE";
    }
}

struct ignite_logger ignite_internal_logger = {
#ifdef IGNITE_CONFIG_DEBUG
    .log_level = LOG_LEVEL_TRACE,
#elifdef IGNITE_CONFIG_RELEASE
    .log_level = LOG_LEVEL_INFO,
#endif
    .error_level = LOG_LEVEL_WARN,
};

struct ignite_logger ignite_client_logger = {
#ifdef IGNITE_CONFIG_DEBUG
    .log_level = LOG_LEVEL_TRACE,
#elifdef IGNITE_CONFIG_RELEASE
    .log_level = LOG_LEVEL_INFO,
#endif
    .error_level = LOG_LEVEL_ERROR,
};

struct ignite_logger ignite_logger_init(enum ignite_log_level log_level,
                                        enum ignite_log_level error_level) {
    return (struct ignite_logger){
        .log_level = log_level,
        .error_level = error_level,
    };
}

void ignite_logger_log(const struct ignite_logger * restrict logger,
                       const enum ignite_log_level log_level,
                       const char *log_message, ...) {
    if (log_level < logger->log_level) {
        return;
    }

    FILE *out = log_level < logger->error_level ? stdout : stderr;
    va_list args;
    va_start(args, log_message);

    fprintf(out, "[%s]: ", ignite_log_level_to_c_string(log_level));
    vfprintf(out, log_message, args);
    fprintf(out, "\n");

    va_end(args);
}
