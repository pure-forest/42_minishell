/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:28:44 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/26 17:28:45 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

static int	create_var(char *envp, t_env_nodes *new_var);

int	create_env(char **envp, t_struct_ptrs *data)
{
	t_env_nodes	*new_var;
	int			i;

	i = -1;
	if (!data || !envp)
		return (EMPTY);
	while (envp[++i])
	{
		new_var = malloc(sizeof(t_env_nodes));
		if (!new_var)
			return (FAIL);
		*new_var = (t_env_nodes){0};
		new_var->base.next = NULL;
		if (create_var(envp[i], new_var))
			return (free(new_var), error_handling(data), FAIL);
		if (append_node((t_list_base **)&data->env, (t_list_base *)new_var))
			return (free_one_env_node(new_var), FAIL);
	}
	return (SUCCESS);
}

static int	create_var(char *envp, t_env_nodes *new_var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(envp, '=');
	if (!equal_sign)
		return (FAIL);
	new_var->var_name = ft_strndup(envp, (equal_sign - envp) + 1);
	if (!new_var->var_name)
		return (FAIL);
	new_var->var_value = ft_strdup(equal_sign + 1);
	if (!new_var->var_value)
		return (free (new_var->var_name), FAIL);
	return (SUCCESS);
}
