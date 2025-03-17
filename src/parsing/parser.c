/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:58:51 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/17 15:31:51 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	print_parser_list(t_cmd_table *parser)
{
	int	fix_dis_index;
	int	fix_dis_cmd;
	int	fix_dis_cmd_args;
	int	fix_dis_redirection;

	fix_dis_index = 6;
	fix_dis_cmd = 10;
	fix_dis_cmd_args = 12;
	fix_dis_redirection = 12;
	printf("---------------------------------------------------------------\n");
	printf("| %-*s | %-*s | %-*s | %-*s |\n", fix_dis_index, "index",
		fix_dis_cmd_args, "input_file", fix_dis_cmd, "command",
		fix_dis_redirection, "redirection");
	printf("---------------------------------------------------------------\n");
	printf("| %-*d | %-*s | %-*s | %-*s |\n", fix_dis_index, parser->index,
		fix_dis_cmd_args, parser->input_file, fix_dis_cmd, parser->cmd,
		fix_dis_redirection, parser->redirection->value);
	// while (parser)
	// {
	// 	printf("| %-*d | %-*s | %-*s | %-*s |\n", fix_dis_index, parser->index,
	// 		fix_dis_cmd, parser->cmd, fix_dis_cmd_args, parser->cmd_args,
	// 		fix_dis_redirection, parser->redirection->value);
	// 	parser = parser->next;
	// }
	printf("--------------------------------------------------------------\n");
}

void	push_to_cmd_table(t_token **token, t_cmd_table **cmd, int index)
{
	t_cmd_table	*temp;

	if (!(*cmd))
	{
		temp = ft_calloc(1, sizeof(t_cmd_table));
		*temp = (t_cmd_table){0};
		if (!temp)
			return ;
	}
	else
		temp = (*cmd);
	temp->index = index;
	if ((*token)->type == OUTPUT || (*token)->type == INPUT)
		temp->redirection = (*token);
	else if ((*token)->type == WORD && (*token)->next != NULL
		&& (*token)->next->type == INPUT)
		temp->input_file = (*token)->value;
	else if ((*token)->type == WORD && (*token)->next == NULL
		&& (*token)->prev->type == INPUT)
		temp->cmd = (*token)->value;
	(*cmd) = temp;
}

void	cmd_table_init(t_token **token, t_cmd_table **cmd)
{
	t_token	*temp;
	int		index;

	index = 0;
	temp = *token;
	while (temp)
	{
		push_to_cmd_table(&temp, cmd, index);
		temp = temp->next;
	}
}
