#ifndef __EXPR_H__
# define __EXPR_H__

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

typedef enum e_token_kind
{
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_VAL,
	TOKEN_MUL,
	TOKEN_ADD,
	TOKEN_SUB,
	TOKEN_START,
	TOKEN_END
}	t_token_kind;

typedef struct s_token {
	t_token_kind	kind;
	size_t			value;
	struct s_token	*next;
}	t_token;

bool	token_list_create(t_token **list, const char *in);

t_token	*lst_new_token(void);
void	lst_add_token(t_token **token_list, t_token *token, t_token_kind kind);
void	lst_destroy(t_token **token_list);
size_t	lst_size(t_token *lst);

typedef enum e_exp_kind
{
	EXP_LPAREN,
	EXP_RPAREN,
	EXP_VAL,
	EXP_MUL,
	EXP_ADD,
	EXP_SUB,
	EXP_MOD,
}	t_exp_kind;

typedef struct s_ast t_ast;

struct s_ast
{
	t_exp_kind	kind;
	union {
		int		value;
		struct	s_binop {
			t_ast	*left;
			t_ast	*right;
		}	binop;
	};
};
bool 	expr_parse(const char *expr, void *dest);

t_ast	*parse_list(t_token *list);
t_ast	*ast_compose(t_token *tokenlist);
t_ast	*ast_new_value(int value);
t_ast	*ast_new_operator(t_token_kind kind);
void	ast_debug(t_ast *ast);
size_t	ast_solve(t_ast *ast);
void 	ast_destroy(t_ast *ast);

#endif /* __EXPR_H__ */