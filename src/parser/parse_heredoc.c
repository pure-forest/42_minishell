/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:16:45 by ydeng             #+#    #+#             */
/*   Updated: 2025/04/26 17:16:46 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static char	*here_doc_put_input(t_struct_ptrs *data, t_token *token);
static int	replace_heredoc_node(t_token **node, char *file_name);
static void	close_stdin(int stdin_copy, int fd, char **file_name,
				t_struct_ptrs *data);
static char	*write_or_expand(int fd, char *file_name, t_token *token,
				t_struct_ptrs *data);

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
					(t_token *)(token_list->base.next));
			if (!heredoc_file)
				return (FAIL);
			if (replace_heredoc_node(&token_list, heredoc_file) == FAIL)
				return (FAIL);
		}
		token_list = (t_token *)(token_list->base.next);
	}
	signal_init();
	return (SUCCESS);
}

static char	*here_doc_put_input(t_struct_ptrs *data, t_token *token)
{
	int		fd;
	char	*file_name;

	file_name = generate_heredoc_name();
	if (!file_name)
		return (NULL);
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (print_error("File open failure", NULL, NULL), NULL);
	file_name = write_or_expand(fd, file_name, token, data);
	if (!file_name)
	{
		free(file_name);
		file_name = NULL;
		return (NULL);
	}
	data->should_delete_heredoc = YES;
	return (file_name);
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
		return (print_error("Malloc failure", NULL, NULL), FAIL);
	new_value[0] = '<';
	temp->value = new_value;
	temp->type = INPUT;
	return (SUCCESS);
}

static char	*write_or_expand(int fd, char *file_name, t_token *token,
		t_struct_ptrs *data)
{
	char	*temp;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy < 0)
		return (print_error("dup2 failure", NULL, NULL), NULL);
	while (1)
	{
		signal_init_heredoc();
		temp = readline("> ");
		if (!temp)
		{
			ft_putstr_fd("warning:here-document delimited by end-of-file\n", 2);
			break ;
		}
		if (g_signal_numb == SIGINT && !temp)
			return (close_stdin(stdin_copy, fd, &file_name, data), NULL);
		if (!ft_strcmp(temp, token->value))
			return (free(temp), close_stdin(stdin_copy, fd, NULL, NULL),
				file_name);
		write_into_temp_file(token, data, fd, &temp);
	}
	return (close_stdin(stdin_copy, fd, &file_name, data), NULL);
}

static void	close_stdin(int stdin_copy, int fd, char **file_name,
					t_struct_ptrs *data)
{
	if (dup2(stdin_copy, STDIN_FILENO) < 0)
	{
		print_error("dup2 failure", NULL, NULL);
		return ;
	}
	close(stdin_copy);
	close(fd);
	if (file_name)
	{
		unlink(*file_name);
		free(*file_name);
		*file_name = NULL;
		if (g_signal_numb)
			data->exit_code = 128 + g_signal_numb;
		else
			data->exit_code = 0;
	}
	g_signal_numb = 0;
	return ;
}
