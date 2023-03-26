#include "expr.h"
#include "xmem.h"
#include <stdlib.h>

void ast_destroy(t_ast *ast)
{
	if (ast->kind == EXP_VAL)
		return ;

	if (ast->binop.left) {
		ast_destroy(ast->binop.left);
		__xfree__(ast->binop.left);
	}
	if (ast->binop.right) {
		ast_destroy(ast->binop.right);
		__xfree__(ast->binop.right);
	}
}