#include <stdio.h>
#include "log.h"
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

static t_log_level log_level = debug;

static inline void get_current_time(char* buffer, size_t buffer_size)
{
    struct timeval tv;
	struct tm tm_time;

    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm_time);
    strftime(buffer, buffer_size, " %H:%M:%S", &tm_time);
    snprintf(buffer + 19, buffer_size - 19, ".%03d", (int)tv.tv_usec / 1000);
}

inline void __log__(t_log_level level, const char* format, ...)
{

#ifndef __LOGGING__
    log_level = warning;
#endif

	if (level < log_level)
        return;

    char ts[24];
    get_current_time(ts, sizeof(ts));

    const char* level_string = log_level_strings[level];
    const char* level_color = log_level_colors[level];

    fprintf(stderr,
		"%s [%s%s%s] ",
        	ts,
			level_color,
			level_string,
			"\033[0m");

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");
}