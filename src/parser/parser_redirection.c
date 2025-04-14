#include "../../inc/parsing.h"

static char	**parse_files(t_token *token, t_token_type type);
static int	parse_outfile(t_token *temp, t_input **input);
static int	parse_infile(t_token *temp, t_input **input);
static char	**parse_files_output_append(t_token *token);

int	parse_redirection(t_token **token, t_input **input)
{
	t_token	*temp;

	temp = *token;
	if (parse_infile(temp, input) == FAIL)
		return (FAIL);
	temp = *token;
	if (parse_outfile(temp, input) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

static int	parse_outfile(t_token *temp, t_input **input)
{
	char	**redir_files;
	t_input	*head;

	redir_files = NULL;
	head = *input;
	while (head)
	{
		redir_files = parse_files_output_append(temp);
		if (!redir_files)
			return (FAIL);
		head->redir_out = redir_files;
		if (is_last_file_append(temp) == YES)
			head->append = YES;
		head = (t_input *)(head->base.next);
		get_next_cmd_node(&temp);
	}
	return (SUCCESS);
}

static int	parse_infile(t_token *temp, t_input **input)
{
	char	**redir_files;
	t_input	*head;

	redir_files = NULL;
	head = *input;
	while (head)
	{
		redir_files = parse_files(temp, INPUT);
		if (redir_files)
			head->redir_in = redir_files;
		else
			return (FAIL);
		head = (t_input *)(head->base.next);
		get_next_cmd_node(&temp);
	}
	return (SUCCESS);
}

static char	**parse_files(t_token *token, t_token_type type)
{
	char	**redir_files;
	int		redir_num;
	int		i;

	redir_num = get_redir_num(token, type);
	redir_files = ft_calloc(redir_num + 1, sizeof(char *));
	i = 0;
	while (token && i < redir_num)
	{
		if (token->type == type)
		{
			redir_files[i] = ft_strdup(((t_token *)(token->base.next))->value);
			if (!redir_files[i])
				return (NULL);
			i++;
		}
		token = (t_token *)(token->base.next);
	}
	redir_files[i] = NULL;
	return (redir_files);
}

static char	**parse_files_output_append(t_token *token)
{
	char	**redir_files;
	int		redir_num;
	int		i;

	redir_num = get_redir_num(token, OUTPUT);
	redir_num += get_redir_num(token, APPEND);
	printf("redir_num = %d\n", redir_num);
	redir_files = ft_calloc(redir_num + 1, sizeof(char *));
	i = 0;
	while (token && i < redir_num)
	{
		if (token->type == OUTPUT || token->type == APPEND)
		{
			redir_files[i] = ft_strdup(((t_token *)(token->base.next))->value);
			if (!redir_files[i])
				return (NULL);
			i++;
		}
		token = (t_token *)(token->base.next);
	}
	redir_files[i] = NULL;
	return (redir_files);
}
