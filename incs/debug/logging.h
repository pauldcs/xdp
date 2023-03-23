#ifndef __LOGGING_H__
# define __LOGGING_H__

# include "libs/libstringf.h"
# include "xdp.h"
# include <unistd.h>
# include <stdlib.h>

enum e_log_lvl {
    Debug,
    Info,
    Warning,
    Error,
    Other
};

# define FATAL_ERROR(fmt, ...) \
    do { \
        fputstr(2,              \
            RED"error"END": " fmt "\n", \
             ##__VA_ARGS__); \
    } while (0)

# ifdef __LOGGING__
#  define __log(level, fmt, ...) \
    do { \
        const char* level_str; \
        switch (level) { \
            case    Info: level_str = GRN" Infor "END; break; \
            case   Debug: level_str = CYN" Debug "END; break; \
            case Warning: level_str = MAG"Warning"END; break; \
            case   Error: level_str = RED" Error "END; break; \
            case   Other: level_str = GRY" Other "END; break; \
            default:      level_str = "Other"; break; \
        } \
        fputstr(2, " [%s] " fmt "\n", level_str, ##__VA_ARGS__); \
} while (0)
# else
#  define __log(level, fmt, ...)
# endif /* __LOGGING__ */

#endif /* __LOGGING_H__ */