#ifndef IGNITE_LOGGING_H_
#define IGNITE_LOGGING_H_

#include <stdio.h>

enum ignite_log_level {
    LOG_LEVEL_TRACE = 0,
    LOG_LEVEL_DEBUG = 20,
    LOG_LEVEL_INFO = 40,
    LOG_LEVEL_WARN = 60,
    LOG_LEVEL_ERROR = 80,
    LOG_LEVEL_CRIT = 100,
    LOG_LEVEL_NO_LOG = 120,
};

const char *ignite_log_level_to_c_string(const enum ignite_log_level log_level);

// TODO: Add logging handlers
struct ignite_logger {
    enum ignite_log_level log_level;
    enum ignite_log_level error_level;
};

extern struct ignite_logger ignite_internal_logger;
extern struct ignite_logger ignite_client_logger;

struct ignite_logger ignite_logger_init(enum ignite_log_level log_level,
                                        enum ignite_log_level error_level);

void ignite_logger_log(const struct ignite_logger *logger,
                       const enum ignite_log_level level, const char *message,
                       ...);

#define IGNITE_INTERNAL_LOG_TRACE(...)                                         \
    ignite_logger_log(&ignite_internal_logger, LOG_LEVEL_TRACE, __VA_ARGS__)

#define IGNITE_INTERNAL_LOG_DEBUG(...)                                         \
    ignite_logger_log(&ignite_internal_logger, LOG_LEVEL_DEBUG, __VA_ARGS__)

#define IGNITE_INTERNAL_LOG_INFO(...)                                          \
    ignite_logger_log(&ignite_internal_logger, LOG_LEVEL_INFO, __VA_ARGS__)

#define IGNITE_INTERNAL_LOG_WARN(...)                                          \
    ignite_logger_log(&ignite_internal_logger, LOG_LEVEL_WARN, __VA_ARGS__)

#define IGNITE_INTERNAL_LOG_ERROR(...)                                         \
    ignite_logger_log(&ignite_internal_logger, LOG_LEVEL_ERROR, __VA_ARGS__)

#define IGNITE_INTERNAL_LOG_CRIT(...)                                          \
    ignite_logger_log(&ignite_internal_logger, LOG_LEVEL_CRIT, __VA_ARGS__)

#define IGNITE_LOG_TRACE(...)                                                  \
    ignite_logger_log(&ignite_client_logger, LOG_LEVEL_TRACE, __VA_ARGS__)

#define IGNITE_LOG_DEBUG(...)                                                  \
    ignite_logger_log(&ignite_client_logger, LOG_LEVEL_DEBUG, __VA_ARGS__)

#define IGNITE_LOG_INFO(...)                                                   \
    ignite_logger_log(&ignite_client_logger, LOG_LEVEL_INFO, __VA_ARGS__)

#define IGNITE_LOG_WARN(...)                                                   \
    ignite_logger_log(&ignite_client_logger, LOG_LEVEL_WARN, __VA_ARGS__)

#define IGNITE_LOG_ERROR(...)                                                  \
    ignite_logger_log(&ignite_client_logger, LOG_LEVEL_ERROR, __VA_ARGS__)

#define IGNITE_LOG_CRIT(...)                                                   \
    ignite_logger_log(&ignite_client_logger, LOG_LEVEL_CRIT, __VA_ARGS__)
#endif // IGNITE_LOGGING_H_
