/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:52:00 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/14 00:52:00 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

void    env(t_struct_ptrs *data)
{
    t_env_nodes   *curr;

    curr = NULL;
    if (data->env)
    {
        curr = data->env;
        while (curr && (curr = curr->next))
        {
            printf("%s\n", curr->str);
            //curr = curr->next;
        }
    }
}