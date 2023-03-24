#include "debug/logging.h"
#include "expr/expr_parser.h"
#include "expr/expr_lexer.h"
#include <stdbool.h>

bool expr_parse(const char *expr, void *dest)
{
    size_t    *dst = (size_t *)dest;
    t_token   *list = NULL;
    t_ast     *ast = NULL;

	if (!token_list_create(&list, expr)) {   
        __log(Error, "Failed to tokenize expression");   
		lst_destroy(&list);
        return(false);
    }
    __log(Info, "Lexer: OK");
    
	if (!(ast = parse_list(list))) {   
        __log(Error, "Failed to create the ast");   
		lst_destroy(&list);
        return (false);
    }

 #ifdef __LOGGING__
    ast_debug(ast);
#endif /* if __LOGGING__ */

	__log(Info, "Parser: OK");

	*dst = ast_solve(ast);

	__log(Info, "-> expression equals %zu", *dst);
    
	lst_destroy(&list);

    return (true);
}