#ifndef __LOGGING_H__
# define __LOGGING_H__

# include "libstringf.h"
# include "hdump.h"
# include <unistd.h>
# include <stdlib.h>

enum e_log_lvl {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    OTHER
};

# define FATAL_ERROR(fmt, ...) \
    do { \
        fputstr(2,              \
            "Fatal: " fmt "\n", \
             ##__VA_ARGS__); \
    } while (0)

# ifdef __LOGGING__
#  define LOG(level, fmt, ...) \
    do { \
        const char* level_str; \
        switch (level) { \
            case    INFO: level_str = GRN " INFOR " END; break; \
            case   DEBUG: level_str = CYN " DEBUG " END; break; \
            case WARNING: level_str = MAG "WARNING" END; break; \
            case   ERROR: level_str = RED " ERROR " END; break; \
            case   OTHER: level_str = GRY " OTHER " END; break; \
            default:      level_str = "OTHER"; break; \
        } \
        fputstr(2, " [%s] " fmt "\n", level_str, ##__VA_ARGS__); \
} while (0)
# else
#  define LOG(level, fmt, ...)
# endif /* __LOGGING__ */
#endif /* __LOGGING_H__ */