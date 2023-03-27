#include "expr.h"
#include "xmem.h"
#include <stdlib.h>

void ast_destroy(t_ast *ast)
{
	if (ast == NULL)
		return;
	if (ast->kind != EXP_VAL)
	{
		ast_destroy(ast->binop.left);
		ast_destroy(ast->binop.right);
	}
	__xfree__(ast);
}