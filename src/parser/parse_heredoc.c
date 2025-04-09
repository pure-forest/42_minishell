#include "../../inc/parsing.h"

static char	*here_doc_put_input(t_struct_ptrs *data, char *deliminator);
static int	replace_heredoc_node(t_token **node, char *file_name);

int	parse_heredoc(t_struct_ptrs *data)
{
	char	*heredoc_file;
	t_token	*token_list;

	token_list = data->token;
	while (token_list)
	{
		if (token_list->type == HEREDOC)
		{
			heredoc_file = here_doc_put_input(data,
					((t_token *)(token_list->base.next))->value);
			if (replace_heredoc_node(&token_list, heredoc_file) == FAIL)
				return (FAIL);
		}
		token_list = (t_token *)(token_list->base.next);
	}
	return (SUCCESS);
}

static char	*here_doc_put_input(t_struct_ptrs *data, char *deliminator)
{
	int		fd;
	char	*temp;
	char	*file_name;

	file_name = generate_heredoc_name();
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		temp = readline("> ");
		if (!ft_strncmp(temp, deliminator, ft_strlen(deliminator)))
		{
			free(temp);
			close(fd);
			return (file_name);
		}
		if (check_for_expansion(data, &temp) == FAIL)
			break ;
		write(fd, temp, ft_strlen(temp));
		free(temp);
		write(fd, "\n", 1);
	}
	close(fd);
	return (NULL);
}

static int	replace_heredoc_node(t_token **node, char *file_name)
{
	t_token	*temp;
	char	*new_value;
	t_token	*deliminator;

	temp = *node;
	deliminator = (t_token *)(temp->base.next);
	free(deliminator->value);
	deliminator->type = INFILE;
	((t_token *)(temp->base.next))->value = file_name;
	free(temp->value);
	new_value = ft_calloc(2, sizeof(char));
	if (!new_value)
		return (FAIL);
	new_value[0] = '<';
	temp->value = new_value;
	temp->type = INPUT;
	return (SUCCESS);
}
