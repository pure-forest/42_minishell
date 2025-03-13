/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:50:59 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/13 20:15:07 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

t_env_nodes	**create_env(char **envp)
{
	
}

//////////////	DEBUGGING THINGS - DELETE
int	main(char **envp)
{
	t_env_nodes	**res;
	int	i = 0;

	res = create_env(envp);
	if (res)
	{
		while (res[i])
	}

	return (0);
}
