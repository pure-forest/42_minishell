#include "../../inc/parsing.h"

static int	modify_input_node(t_token *temp, t_input **input);
static int	parse_files(t_token *token, t_redir **head);

int	parse_redirection(t_token **token, t_input **input)
{
	t_token	*temp;
	t_input	*temp_input;

	temp = *token;
	temp_input = *input;
	while (temp_input)
	{
		if (modify_input_node(temp, &temp_input) == FAIL)
			return (FAIL);
		temp_input = (t_input *)(temp_input->base.next);
		get_next_cmd_node(&temp);
	}
	return (SUCCESS);
}

static int	modify_input_node(t_token *temp, t_input **input)
{
	t_redir	*redirection;
	t_input	*head;

	head = *input;
	if (get_redir_num(temp) == 0)
		return (SUCCESS);
	else
	{
		redirection = NULL;
		if (parse_files(temp, &redirection) == FAIL)
			return (FAIL);
		if (!redirection)
			return (FAIL);
		head->redirection = redirection;
	}
	return (SUCCESS);
}

static int	parse_files(t_token *token, t_redir **head)
{
	int		redir_num;
	t_redir	*temp;
	int		i;

	i = 0;
	redir_num = get_redir_num(token);
	while (token && i < redir_num)
	{
		if (token->type == INFILE || token->type == OUTFILE
			|| token->type == OUTFILE_APPEN)
		{
			temp = redirection_init(token->type, token->value);
			if (!temp)
				return (print_error("Malloc failure", NULL, NULL),
					free_redir(head), FAIL);
			if (!(*head))
				*head = temp;
			else if (append_node((t_list_base **)(head),
				(t_list_base *)temp) == FAIL)
				return (FAIL);
			i++;
		}
		token = (t_token *)(token->base.next);
	}
	return (SUCCESS);
}
