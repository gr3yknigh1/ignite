#include "ignite/logging.h"

#include <stdarg.h>
#include <stdio.h>

c_str ignite_log_level_to_c_str(const enum ignite_log_level log_level) {
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
    case LOG_LEVEL_NO_LOG:
        return "NOLOG";
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

void ignite_logger_log(const struct ignite_logger *restrict logger,
                       const enum ignite_log_level log_level, c_str log_message,
                       ...) {
    if (log_level < logger->log_level) {
        return;
    }

    FILE *out = log_level < logger->error_level ? stdout : stderr;
    va_list args;
    va_start(args, log_message);

    fprintf(out, "[%s]: ", ignite_log_level_to_c_str(log_level));

    // NOTE: `clang-tidy` says that `args` is uninitalized. This is a bug in
    // `clang-tidy`. Because of that we forced to ignore this error. Reference:
    // <https://bugs.llvm.org/show_bug.cgi?id=41311>

    // NOLINTNEXTLINE(clang-analyzer-valist.Uninitialized)
    vfprintf(out, log_message, args);

    fprintf(out, "\n");
    va_end(args);
}
