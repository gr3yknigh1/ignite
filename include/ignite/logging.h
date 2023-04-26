#ifndef IGNITE_LOGGING_H_
#define IGNITE_LOGGING_H_

enum ignite_log_level {
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_CRIT,
};

struct ignite_logger {
    enum ignite_log_level log_level;
};

extern struct ignite_logger core_logger;

void ignite_log(const enum ignite_log_level level, const char *message, ...);

#define IGNITE_LOG_TRACE(__message, ...)
#define IGNITE_LOG_DEBUG(__message, ...)
#define IGNITE_LOG_INFO(__message, ...)
#define IGNITE_LOG_WARN(__message, ...)
#define IGNITE_LOG_ERROR(__message, ...)
#define IGNITE_LOG_CRIT(__message, ...)

#endif // IGNITE_LOGGING_H_
