#include "hdump.h"
#include "libstringf.h"
#include "utils.h"
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

bool parse_argument(const char *argument, t_dump_params *params, int *ac, char ***av)
{
    char *arg;

    if (!strncmp(argument, "--size", 6)) {
        if (*(argument + 6) == '=') {
            if (!str_to_uint64(
                    argument + 7,
                    &params->file.range_size))
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);
        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!str_to_uint64(
                arg,
                &params->file.range_size))
                return (report_error("'%s': %s\n", argument, "Invalid format"),
                    false);
        } else 
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);

    } else if (!strncmp(argument, "--start", 7)) {
        if (*(argument + 7) == '=') {
            if (!str_to_uint64(
                    argument + 8,
                    &params->file.start_offset))
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);
        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!str_to_uint64(
                arg,
                &params->file.start_offset))
                return (report_error("'%s': %s\n", argument, "Invalid format"),
                    false);
        } else 
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);

    } else if (!strcmp(argument, "-")) {
        params->is_stdin = true;

    } else if (!strcmp(argument, "-r")
           || !strcmp(argument, "--raw")) {
        params->mode = DUMP_RAW;

    } else if (!strncmp(argument, "--string", 8)) {
        params->mode = DUMP_STRINGS;
        if (*(argument + 8) == '=') {
            if (!str_to_uint64(
                    argument + 9,
                    &params->string_size))
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);
        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!str_to_uint64(
                arg,
                &params->string_size))
                return (report_error("'%s': %s\n", argument, "Invalid format"),
                    false);
        } else 
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);

    } else if (!strcmp(argument, "-c")
             ||!strcmp(argument, "--color")) {
        params->colored_output = true;

    } else if (!strcmp(argument, "-h")
            || !strcmp(argument, "--help")) {
        __usage();
        exit (0);

    } else if (!params->file.filename) {
        params->file.filename = argument;
    } else {
        return (report_error("'%s': %s\n", argument, "Unrecognized argument"),
                false);
    }
    return (true);
}