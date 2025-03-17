/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:50:59 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/16 23:22:10 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

static void		append_node(t_struct_ptrs *data, t_env_nodes *new_var);
static t_env_nodes	*find_last(t_env_nodes *root);

int	create_env(char **envp, t_struct_ptrs *data)
{
	t_env_nodes	*new_var;
	int			i;

	i = -1;
	if (!(data))
		return (0);
	while (envp[++i])
	{
		new_var = malloc(sizeof(t_env_nodes));
		if (!new_var)
			return (0);
		*new_var = (t_env_nodes){0};
		new_var->str = ft_strdup(envp[i]);
		if (!new_var->str)
			return (free(new_var), error_handling(data), -1);
		new_var->first_letter = new_var->str[0];
		new_var->next = NULL;
		if (!data->env)
		{
			data->env = new_var;
			new_var->prev = NULL;
		}
		else
			append_node(data, new_var);
	}
	return (1);
}

static void	append_node(t_struct_ptrs *data, t_env_nodes *new_var) //Static or not?
{
	t_env_nodes	*last_var;

	last_var = find_last(data->env);
	last_var->next = new_var;
	new_var->prev = last_var;
}

static t_env_nodes	*find_last(t_env_nodes *root) //static or not??
{
	if (!root)
		return (NULL);
	while (root->next)
		root = root->next;
	return (root);
}

/*
//////////////	DEBUGGING THINGS - DELETE
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_struct_ptrs	data;
	//int	i = 0;

	data = (t_struct_ptrs){0};
	if (!(create_env(envp, &data)))
		return (-1);
	t_env_nodes *curr;
	curr = data.env;
	while(i <= 3)
	{
		printf("Node[%d]: Value: %p\nStr: '%s'\nNext: %p   Prev: %p\n\n",i, (void *)curr, curr->str, (void *)curr->next, (void *)curr->prev);
		curr = curr->next;
		i++;
	}

	while(curr->next)
	{
		printf("%s\n", curr->str);
		curr = curr->next;
		i++;
	}
	env(&data);
	free_nodes(&data.env);
	return (0);
}*/
