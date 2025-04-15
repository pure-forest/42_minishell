#include "../../inc/utils.h"

t_token	*token_init(t_token_type type, char *token_value)
{
	t_token	*node;

	if (!token_value)
		return (NULL);
	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = token_value;
	node->quote_count = 0;
	node->quote_mark = 0;
	node->should_expand = YES;
	node->expand_heredoc = YES;
	node->expanded_value = NULL;
	node->type = type;
	node->base.next = NULL;
	node->base.prev = NULL;
	return (node);
}

t_input	*cmd_table_init(char **cmd_arr)
{
	t_input	*temp;

	if (!cmd_arr)
		return (NULL);
	temp = ft_calloc(1, sizeof(t_input));
	if (!temp)
		return (NULL);
	temp->cmd_arr = cmd_arr;
	temp->append = NO;
	temp->redir_in = NULL;
	temp->redir_out = NULL;
	temp->base.next = NULL;
	temp->base.prev = NULL;
	return (temp);
}
