#include "hdump.h"
#include "libstringf.h"
#include "logging.h"
#include "expr_parser.h"
#include "expr_lexer.h"
#include "utils.h"
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>


static bool parse_expr(const char *expr, size_t *dst)
{
    t_token		*list = NULL;

	if (!*expr
		|| !token_list_create(&list, expr)) {   
        LOG(ERROR, "Failed to tokenize expression");   
		return (lst_destroy(&list), false);
    }
    LOG(INFO, "Lexer: OK");
	t_ast *ast = parser(list);
    
	if (!ast)
    {   
        LOG(ERROR, "Failed to generate AST");   
		return (lst_destroy(&list), false);
    }
    LOG(INFO, "Parser: OK");
#ifdef __LOGGING__
    ast_debug(ast);
#endif
	
	*dst = ast_solve(ast);
	LOG(OTHER, "-> expression equals %d", *dst);
	lst_destroy(&list);
    return (true);
}

bool parse_argument(const char *argument, t_dump_params *params, int *ac, char ***av)
{
    char *arg;

    if (!strncmp(argument, "--size", 6)) {
        LOG(DEBUG, "parsing argument '--size'");
        if (*(argument + 6) == '=') {
            if (!parse_expr(
                    argument + 7,
                    &params->file.range_size))
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);
        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!parse_expr(
                arg,
                &params->file.range_size))
                return (report_error("'%s': %s\n", argument, "Invalid format"),
                    false);
        } else 
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);

    } else if (!strncmp(argument, "--start", 7)) {
        LOG(DEBUG, "parsing argument '--start'");
        if (*(argument + 7) == '=') {
            if (!parse_expr(
                    argument + 8,
                    &params->file.start_offset))
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);
        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!parse_expr(
                arg,
                &params->file.start_offset))
                return (report_error("'%s': %s\n", argument, "Invalid format"),
                    false);
        } else 
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);

    } else if (!strcmp(argument, "-")) {
        LOG(DEBUG, "Enabling stdin as input");
        params->is_stdin = true;

    } else if (!strcmp(argument, "-r")
           || !strcmp(argument, "--raw")) {
        LOG(DEBUG, "Setting mode as: raw");
        params->mode = DUMP_RAW;

    } else if (!strncmp(argument, "--string", 8)) {
        LOG(DEBUG, "parsing argument '--string'");
        params->mode = DUMP_STRINGS;
        if (*(argument + 8) == '=') {
            if (!parse_expr(
                    argument + 9,
                    &params->string_size))
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);
        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!parse_expr(
                arg,
                &params->string_size))
                return (report_error("'%s': %s\n", argument, "Invalid format"),
                    false);
        } else 
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);

    } else if (!strcmp(argument, "-c")
             ||!strcmp(argument, "--color")) {
        LOG(DEBUG, "Enabling colors");
        params->colored_output = true;

    } else if (!strcmp(argument, "-h")
            || !strcmp(argument, "--help")) {
        __usage();
        exit (0);

    } else if (!params->file.filename) {
        params->file.filename = argument;
    } else {
        LOG(ERROR, "'%s': Could not be parsed", argument);
        return (report_error("'%s': %s\n", argument, "Unrecognized argument"),
                false);
    }
    return (true);
}