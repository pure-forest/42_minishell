/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:51:25 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/16 18:51:25 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

//////////////	DEBUGGING THINGS - DELETE
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_struct_ptrs	data;
	int	i = 0;

	data = (t_struct_ptrs){0};
	if (!(create_env(envp, &data)))
		return (-1);
   if (!(create_export(&data)))
		return (-1);
	t_env_nodes *curr;
	//t_export *curr;
	curr = data.export;
	/*while(i <= 3)
	{
		printf("Node[%d]: Value: %p\nStr: '%s'\nNext: %p   Prev: %p\n\n",i, (void *)curr, curr->str, (void *)curr->next, (void *)curr->prev);
		curr = curr->next;
		i++;
	}*/

	if (curr)
	{
		while(curr) // && (curr = curr->next))
		{
			printf("%s\"%s\"\n", curr->var_name, curr->var_value);
			//printf("%s\n", curr->var_name);
			//printf("%s\n", curr->var_value);
			//printf("%c\n", curr->first_letter);
			curr = (t_env_nodes *)curr->base.next;
			i++;
		}
	}
	//env(&data);
    //pwd(&data);

	free_env_nodes(&data.env);
	free_env_nodes(&data.export);
	return (0);
}
