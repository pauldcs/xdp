#ifndef __LOG_H__
# define __LOG_H__

# include <string.h>
# include <errno.h>

# define C_BLACK     "\e[0;30m"
# define C_RED       "\e[0;31m"
# define C_GREENN    "\e[0;32m"
# define C_YELLOW    "\e[0;33m"
# define C_BLUE      "\e[0;34m"
# define C_MAGENTA   "\e[0;35m"
# define C_CYAN      "\e[0;36m"
# define C_LIGHTGREY "\x1b[37;1m"
# define C_WHITE     "\x1b[2;37m"
# define C_GREY      "\x1b[90m"
# define C_RESET     "\e[0m"

# define ERROR_MSG strerror(errno)

typedef enum e_log_level{
    debug,
    info,
    warning,
    error,
    fatal
} t_log_level;

static const char* log_level_strings[] = {
    [debug]    = "debug",
    [info]     = "info",
    [warning]  = "warning",
    [error]    = "error",
    [fatal]    = "fatal"
};

static const char* log_level_colors[] = {
    [debug]    = "\e[0;33m",
    [info]     = "\e[0;34m",
    [warning]  = "\e[0;35m",
    [error]   = "\e[0;31m",
    [fatal]   = "\e[1;31m"
};

void log_message(t_log_level level, const char* format, ...);

#endif /* __LOG_H__ */