/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:55:29 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/16 19:55:29 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	set_var(t_env_nodes *new_var, t_env_nodes *env);
//static int fill_new_var(t_export *new_var, char *envp_var);
static void	append_node(t_struct_ptrs *data, t_env_nodes *new_var);
static t_env_nodes    *find_last(t_env_nodes *root);
static int	is_export_sorted(t_env_nodes *env);

int create_export(t_struct_ptrs *data)
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
		new_var->next = NULL;
		set_var(new_var, data->env);
		// check return ??
		if (!data->export)
		{
			data->export = new_var;
			new_var->prev = NULL;
		}
		else
			append_node(data, new_var);
	}
	return (1);
}

void	set_var(t_env_nodes *new_var, t_env_nodes *env)
{
	t_env_nodes	*smallest;
	t_env_nodes	*curr;
	int			min_letter;
	
	min_letter = 127;
	curr = env;
	smallest = NULL;
	while (curr)
    {
        if ((curr->first_letter < min_letter) && curr->copied == 0)
		{
			min_letter = curr->first_letter;
            smallest = curr;
		}
		curr = curr->next;
    }
	if (!smallest)
		return ;
	new_var->str = ft_strjoin("declare -x ", smallest->str);
	// MISSING MALLOC CHECK
	//new_var->copied = 1;
	smallest->copied = 1;
}

/*static int fill_new_var(t_export *new_var, char *envp_var)
{
	char    *tmp; 

	tmp = ft_strdup(envp_var);
	if (!tmp)
		return (0);
	new_var->first_letter = tmp[0];
	new_var->str = ft_strjoin("declare -x ", tmp);
	free(tmp);
	if (!new_var->str)
		return (0);
	return (1);
}*/

static void	append_node(t_struct_ptrs *data, t_env_nodes *new_var)  //Static or not??
{
	t_env_nodes	*last_var;

	last_var = find_last(data->export);
	last_var->next = new_var;
	new_var->prev = last_var;
}

static t_env_nodes    *find_last(t_env_nodes *root) //static or not??
{
	if (!root)
		return (NULL);
	while (root->next)
		root = root->next;
	return (root);
}

static int	is_export_sorted(t_env_nodes *env)
{
	t_env_nodes	*curr;

	curr = env;
	while (curr)
	{
		if (curr->copied == 0)
			return (1);
		curr = curr->next;
	}
	return (0);
}