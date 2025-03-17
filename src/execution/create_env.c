/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:50:59 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/17 16:12:49 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	create_var(char *envp, t_env_nodes *new_var);

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
		if (!(create_var(envp[i], new_var)))
			return (free(new_var), error_handling(data), -1);
		new_var->base.next = NULL;
		if (!data->env)
		{
			data->env = new_var;
			new_var->base.prev = NULL;
		}
		else
			append_node((t_list_base *)data->env, (t_list_base *)new_var);
	}
	return (1);
}

int	create_var(char *envp, t_env_nodes *new_var)
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

void	append_node(t_list_base *list_to_modify, t_list_base *new_var)
{
	t_list_base	*last_var;

	last_var = find_last(list_to_modify);
	last_var->next = new_var;
	new_var->prev = last_var;
}

t_list_base	*find_last(t_list_base *root)
{
	if (!root)
		return (NULL);
	while (root->next)
		root = root->next;
	return (root);
}

char	*ft_strndup(const char *s, size_t len)	//Not static right?
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	str = (char *) malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!str)
		return (NULL);
	while (s[i] && i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
