#ifndef __LOGGING_H__
# define __LOGGING_H__

# include "xdp.h"
# include "xtypes.h"
# include <stdio.h>
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
        fprintf(stderr,              \
            C_RED "error:" C_RESET " " fmt "\n", \
             ##__VA_ARGS__); \
    } while (0)

# ifdef __LOGGING__
#  define __log(level, fmt, ...) \
    do { \
        const char* level_str; \
        switch (level) { \
            case    Info: level_str = C_GREENN " Infor " C_RESET; break; \
            case   Debug: level_str = C_CYAN " Debug " C_RESET; break; \
            case Warning: level_str = C_MAGENTA "Warning" C_RESET; break; \
            case   Error: level_str = C_RED " Error " C_RESET; break; \
            case   Other: level_str = C_GREY " Other " C_RESET; break; \
            default:      level_str = "Other"; break; \
        } \
        fprintf(stderr, " [%s] " fmt "\n", level_str, ##__VA_ARGS__); \
} while (0)
# else
#  define __log(level, fmt, ...)
# endif /* __LOGGING__ */

#endif /* __LOGGING_H__ */