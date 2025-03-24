/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:50:59 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/22 09:10:54 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int		create_var(char *envp, t_env_nodes *new_var);
char	*ft_strndup(const char *s, size_t len);

int	create_env(char **envp, t_struct_ptrs *data)
{
	t_env_nodes	*new_var;
	int			i;

	i = -1;
	if (!(data))
		return (0);
	//printf("Address of data inside create_env: %p\n", (void *)data);
	//printf("Address of data.env inside create_env: %p\n", (void *)data->env);
	while (envp[++i])
	//while (++i < 4)
	{
		new_var = malloc(sizeof(t_env_nodes));
		if (!new_var)
			return (0);
		*new_var = (t_env_nodes){0};
		new_var->base.next = NULL;
		if (!(create_var(envp[i], new_var)))
			return (free(new_var), error_handling(data), -1);
		if (!data->env)
		{
			data->env = new_var;
			new_var->base.prev = NULL;
			//printf("First node added: %s\n", new_var->var_name);
		}
		else
		{
			if (append_node((t_list_base *)data->env, (t_list_base *)new_var))
				return (FAIL);
			//printf("Node added: %s\n", new_var->var_name);
		}
	}
	//printf("Final address of data->env in create_env: %p\n", (void *)data->env);
	return (1);
}

int	create_var(char *envp, t_env_nodes *new_var) //static or not??
{
	char	*equal_sign;

	equal_sign = ft_strchr(envp, '=');
	if (!equal_sign)
		return (0);
	new_var->var_name = ft_strndup(envp, (equal_sign - envp) + 1); //+1 is there to copy in the =, per evitare di doverlo copiare dopo? Serve? o e' meglio farlo quando si stampa?
	if (!new_var->var_name)
		return (0);
	new_var->var_value = ft_strdup(equal_sign + 1); //qui il +1 c'e per copiare dopo il =, dato che strchr ritorna un pointer iniziando al =
	if (!new_var->var_value)
		return (free (new_var->var_name), 0);
	return (1);
}
