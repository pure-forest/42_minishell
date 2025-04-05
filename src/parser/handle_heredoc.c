#include "../../inc/parsing.h"

static char	*generate_heredoc_name(void);
static char	*here_doc_put_input(char *deliminator);
static int		replace_heredoc_node(t_token **node, char *file_name);

int	parse_heredoc(t_struct_ptrs *data)
{
	char	*heredoc_file;
	t_token	*token_list;

	token_list = data->token;
	while (token_list)
	{
		if (token_list->type == HEREDOC)
		{
			heredoc_file = here_doc_put_input(((t_token *)(token_list->base.next))->value);
			if (replace_heredoc_node(&token_list, heredoc_file) == FAIL)
				return (FAIL);
			printf("heredoc_file = %s\n", heredoc_file);
		}
		token_list = (t_token *)(token_list->base.next);
	}
	return (SUCCESS);
}

static char	*generate_heredoc_name(void)
{
	static int	index;
	char		*number_str;
	char		*file_name;

	number_str = ft_itoa(index);
	if (!number_str)
		return (NULL);
	file_name = ft_strjoin(HEREDOC_TEMP_NAME, number_str);
	free(number_str);
	index++;
	// printf("file name = %s\n", file_name);
	return (file_name);
}

static char	*here_doc_put_input(char *deliminator)
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
		write(1, "> ", 2);
		temp = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(temp, deliminator, ft_strlen(deliminator)))
		{
			free(temp);
			close(fd);
			return (file_name);
		}
		write(fd, temp, ft_strlen(temp));
		free(temp);
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
	new_value = ft_calloc(2, sizeof(char));
	if (!new_value)
		return (FAIL);
	new_value[0] = '<';
	temp->value = new_value;
	temp->type = INPUT;
	return (SUCCESS);
}
