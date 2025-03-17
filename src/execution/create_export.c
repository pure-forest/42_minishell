/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/03/16 19:55:29 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/16 19:55:29 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int			set_var(t_env_nodes *new_var, t_env_nodes *env);
static int	is_export_sorted(t_env_nodes *env);
int			ft_strcmp(char *s1, char *s2);

int	create_export(t_struct_ptrs *data)
{
	t_env_nodes	*new_var;

	if (!(data))
		return (0);
	while (is_export_sorted(data->env))
	{
		new_var = malloc(sizeof(t_env_nodes));
		if (!new_var)
			return (0);
		*new_var = (t_env_nodes){0};
		new_var->base.next = NULL;
		set_var(new_var, data->env);
		// check return ??
		if (!data->export)
		{
			data->export = new_var;
			new_var->base.prev = NULL;
		}
		else
			append_node((t_list_base *)data->export, (t_list_base *)new_var);
	}
	return (1);
}

int	set_var(t_env_nodes *new_var, t_env_nodes *env)
{
	t_env_nodes	*smallest;
	t_env_nodes	*curr;

	curr = env;
	smallest = NULL;
	while (curr)
	{
		if ((!smallest || ft_strcmp(curr->var_name, smallest->var_name) < 0)
			&& curr->copied == 0)
			smallest = curr;
		curr = (t_env_nodes *)curr->base.next;
	}
	if (!smallest)
		return (0);
	new_var->var_name = ft_strjoin("declare -x ", smallest->var_name);
	if (!new_var->var_name)
		return (0);
	new_var->var_value = ft_strdup(smallest->var_value);
	if (!new_var->var_value)
		return (free(new_var->var_name), 0);
	smallest->copied = 1;
	return (1);
}

static int	is_export_sorted(t_env_nodes *env)
{
	t_env_nodes	*curr;

	curr = env;
	while (curr)
	{
		if (curr->copied == 0)
			return (1);
		curr = (t_env_nodes *)curr->base.next;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2) // static or not??
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
