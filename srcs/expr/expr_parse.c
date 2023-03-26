#include "log.h"
#include "expr.h"
#include "expr.h"
#include "xmem.h"
#include <stdbool.h>

bool expr_parse(const char *expr, void *dest)
{
    size_t    *dst = (size_t *)dest;
    t_token   *list = NULL;
    t_ast     *ast = NULL;

	if (!token_list_create(&list, expr)) {   
        log_message(error, "Failed to tokenize expression");   
		lst_destroy(&list);
        return(false);
    }
    log_message(info, "Lexer: OK");
    
	if (!(ast = parse_list(list))) {   
        log_message(error, "Failed to create the ast");   
		lst_destroy(&list);
        return (false);
    }

#ifdef __LOGGING__
    ast_debug(ast);
#endif

	log_message(info, "Parser: OK");
	*dst = ast_solve(ast);
	log_message(info, "-> expression equals %zu", *dst);
	lst_destroy(&list);
    //ast_destroy(ast);
    //__xfree__(ast);
    return (true);
}