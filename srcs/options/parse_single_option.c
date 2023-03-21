#include "hdump.h"
#include "logging.h"
#include "utils.h"
#include "expr/expr_parser.h"
#include "expr/expr_lexer.h"
#include <string.h>
#include <stdbool.h>

static bool parse_expr(const char *expr, size_t *dst)
{
    t_token   *list = NULL;
    t_ast     *ast = NULL;

	if (!token_list_create(&list, expr)) {   
        LOG(ERROR, "Failed to tokenize expression");   
		lst_destroy(&list);
        return(false);
    }
    LOG(INFO, "Lexer: OK");
    
	if (!(ast = parser(list))) {   
        LOG(ERROR, "Failed to create the ast");   
		lst_destroy(&list);
        return (false);
    }
    LOG(INFO, "Parser: OK");

 #ifdef __LOGGING__
    //ast_debug(ast);
#endif /* if __LOGGING__ */
	
	*dst = ast_solve(ast);

	LOG(OTHER, "-> expression equals %d", *dst);
	lst_destroy(&list);
    return (true);
}

bool parse_single_option(const char *argument, t_dump_params *params, int *ac, char ***av)
{
    char *arg;

    if (!strncmp(argument, "--size", 6)) {
        LOG(DEBUG, "parsing argument '--size'");
        if (*(argument + 6) == '=') {
            if (!parse_expr(
                    argument + 7,
                    &params->file.range_size))
            return (report_error("'%s': %s\n", argument, "Invalid"),
                false);

        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!parse_expr(
                arg,
                &params->file.range_size))
                return (report_error("'%s': %s\n", argument, "Invalid"),
                    false);

        } else 
            return (report_error("'%s': %s\n", argument, "Invalid"),
                false);

    } else if (!strncmp(argument, "--start", 7)) {
        LOG(DEBUG, "parsing argument '--start'");
        if (*(argument + 7) == '=') {
            if (!parse_expr(
                    argument + 8,
                    &params->file.start_offset))
            return (report_error("'%s': %s\n", argument, "Invalid"),
                false);
        
        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!parse_expr(
                arg,
                &params->file.start_offset))
                return (report_error("'%s': %s\n", argument, "Invalid"),
                    false);
        
        } else 
            return (report_error("'%s': %s\n", argument, "Invalid"),
                false);

    // } else if (!strcmp(argument, "-r")
    //        || !strcmp(argument, "--raw")) {
    //     LOG(DEBUG, "Setting mode as: raw");
    //     params->mode = DUMP_RAW;

    // } else if (!strncmp(argument, "--string", 8)) {
    //     LOG(DEBUG, "parsing argument '--string'");
    //     params->mode = DUMP_STRINGS;
    //     if (*(argument + 8) == '=') { 
    //         if (!parse_expr(
    //                 argument + 9,
    //                 &params->string_size))
    //         return (report_error("'%s': %s\n", argument, "Invalid"),
    //             false);
        
    //     } else if ((arg = get_next_argument(ac, av)) != NULL) {
    //         if (!parse_expr(
    //             arg,
    //             &params->string_size))
    //             return (report_error("'%s': %s\n", argument, "Invalid"),
    //                 false);
    //     } else 
    //         return (report_error("'%s': %s\n", argument, "Invalid"),
    //             false);

    //} else if (!strcmp(argument, "-c")
    //         ||!strcmp(argument, "--color")) {
    //    LOG(DEBUG, "Enabling colors");
    //    params->colored_output = true;

    } else if (!strcmp(argument, "-h")
            || !strcmp(argument, "--help")) {
        usage();
        exit (0);

    } else if (!params->file.filename) {
        params->file.filename = argument;
    
    } else {
        FATAL_ERROR("'%s': Could not be parsed", argument);
        return (false);
    }
    return (true);
}