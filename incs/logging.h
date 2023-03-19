#ifndef __LOGGING_H__
# define __LOGGING_H__

# include "libstringf.h"
# include <unistd.h>
# include <stdlib.h>

enum e_log_lvl {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

# ifdef __LOGGING__
#  define LOG(level, fmt, ...) \
    do { \
        const char* level_str; \
        switch (level) { \
            case    INFO: level_str = BLU    "INFO" END; break; \
            case   DEBUG: level_str = YEL   "DEBUG" END; break; \
            case WARNING: level_str = MAG "WARNING" END; break; \
            case   ERROR: level_str = RED   "ERROR" END; break; \
            case   FATAL: level_str = RED   "FATAL" END; break; \
            default:      level_str = "OTHER"; break; \
        } \
        fputstr(2, "[%s] " fmt "\n", level_str, ##__VA_ARGS__); \
} while (0)

#  define FATAL_ERROR(fmt, ...) \
    do { \
        fputstr(2,                  \
            "[%s:%d] Fatal: " fmt "\n",         \
            __FILE__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#  define ASSERT(expr) \
    do { \
        if (!(expr)) {                              \
            fputstr(2,                  \
                "[%s:%d] Assertion failed: '%s'\n", \
                __FILE__, __LINE__, #expr);         \
            abort();                                \
        } \
    } while (0)

# else
#  define LOG(level, fmt, ...)
#  define FATAL_ERROR(fmt, ...) 
#  define ASSERT(expr) 
# endif /* __LOGGING__ */
#endif /* __LOGGING_H__ */