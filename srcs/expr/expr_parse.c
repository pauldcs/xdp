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
        __log__(error, "Failed to tokenize expression");   
		lst_destroy(&list);
        return(false);
    }
    __log__(info, "Lexer: OK");
    
	if (!(ast = parse_list(list))) {   
        __log__(error, "Failed to create the ast");   
		lst_destroy(&list);
        return (false);
    }

#ifdef __LOGGING__
    ast_debug(ast);
#endif

	__log__(info, "Parser: OK");
	*dst = ast_solve(ast);
	__log__(info, "-> expression equals %zu", *dst);
	lst_destroy(&list);
    ast_destroy(ast);
    return (true);
}