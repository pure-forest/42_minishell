/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:58:51 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/25 16:41:28 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	print_parser_list(t_cmd_table *parser)
{
	int	fix_dis_index;
	int	fix_dis_cmd;
	int	fix_dis_cmd_args;
	// int	fix_dis_redirection;

	fix_dis_index = 6;
	fix_dis_cmd = 10;
	fix_dis_cmd_args = 12;
	// fix_dis_redirection = 12;
	printf("-----------------------------------------------------------------------------------------------\n");
	printf("| %-*s | %-*s |  %-*s |  %-*s | %-*s | %-*s |\n", fix_dis_index, "index",
		fix_dis_cmd_args, "input_file", fix_dis_cmd_args,
		"cmd args[0]",fix_dis_cmd_args, "cmd args[1]",
		fix_dis_cmd, "command", fix_dis_cmd, "redirection");
	while (parser)
	{
		printf("-----------------------------------------------------------------------------------------------\n");
		printf("| %-*d | %-*s |  %-*s |  %-*s | %-*s | %-*d |\n", fix_dis_index, parser->index,
			fix_dis_cmd_args, parser->input_file, fix_dis_cmd_args, parser->cmd_args[0],
			fix_dis_cmd_args, parser->cmd_args[1], fix_dis_cmd, parser->cmd,
			fix_dis_cmd, parser->redirection);
		parser = parser->next;
	}
	printf("-----------------------------------------------------------------------------------------------\n");
}

char	**find_pipe(char *str)
{
	char	**pipe_str;

	if (ft_strchr(str, '|'))
	{
		pipe_str = ft_split(str, '|');
		if (!pipe_str)
			return (NULL);
		return (pipe_str);
	}
	return (NULL);
}

void	trim_and_free(char **src)
{
	char	*temp;

	temp = ft_strtrim((*src), " ");
	if (!temp)
	{
		free(*src);
		*src = NULL;
		return ;
	}
	free(*src);
	*src = temp;
}

int		check_for_redirection(char ***cmd_args)
{
	int	i = 0;
	char **args = (*cmd_args);

	while (args[i])
	{
		if (!ft_strncmp(args[i], "<", 1))
		{
			args[i] = args[i + 1];
			return (STDIN_FILENO);
		}

		else if (!ft_strncmp(args[i], ">", 1))
		{
			// while (args[i])
			// 	args[i] = args[i + 1];
			return (STDOUT_FILENO);
		}
		i++;
	}
	return (1);
}

char	*check_for_cmd(char **cmd_args)
{
	int i = 0;
	char	*cmd;

	while (cmd_args[i])
	{
		if (ft_strchr(cmd_args[i], ' '))
			trim_and_free(&cmd_args[i]);
		if (ft_strnstr(cmd_args[i], "cat", 3)
			||ft_strnstr(cmd_args[i], "echo", 4)
			|| ft_strnstr(cmd_args[i], "cd", 2)
			|| ft_strnstr(cmd_args[i], "pwd", 3)
			||  ft_strnstr(cmd_args[i], "unset", 5)
			|| ft_strnstr(cmd_args[i], "export", 6)
			|| ft_strnstr(cmd_args[i], "env", 3)
			|| ft_strnstr(cmd_args[i], "exit", 4)
			|| ft_strnstr(cmd_args[i], "grep", 4))
			return (cmd_args[i]);
		else
			cmd = NULL;
		i++;
	}
	return (cmd);
}

void	push_to_cmd_table(t_cmd_table **cmd, int index, char **cmd_args)
{
	t_cmd_table	*temp;

	temp = ft_calloc(1, sizeof(t_cmd_table));
	*temp = (t_cmd_table){0};
	if (!temp)
		return ;
	temp->index = index;
	temp->redirection = check_for_redirection(&cmd_args);
	if (temp->redirection == STDIN_FILENO)
		temp->input_file = cmd_args[1];
	temp->cmd_args = cmd_args;
	temp->cmd = check_for_cmd(cmd_args);
	temp->next = (*cmd);
	(*cmd) = temp;
}

void	cmd_table_init(char *str, t_cmd_table **cmd)
{
	int		i;
	char	**split_str;
	char	**cmd_args;

	i = 0;
	split_str = NULL;
	cmd_args = NULL;
	if (ft_strchr(str, '|'))
		split_str = find_pipe(str);
	else
		split_str[0] = str;
	while (split_str[i])
	{
		printf("split_str[%d] = %s\n", i, split_str[i]);
		if (ft_strchr(split_str[i], ' '))
		{
			cmd_args = ft_split(split_str[i], ' ');
			free(split_str[i]);
			push_to_cmd_table(cmd, i, cmd_args);
		}
		else
			push_to_cmd_table(cmd, i, cmd_args);
		i++;
	}
	free(split_str);
}
