#ifndef __EXPR_LEXER_H__
# define __EXPR_LEXER_H__

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

#endif /* __EXPR_LEXER_H__ */
