/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:54:36 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/16 19:54:36 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

int    export(t_struct_ptrs *data)
{
    t_env_nodes   *curr;

    curr = NULL;
    if (data->export)
    {
        curr = data->export;
        while (curr)
        {
            if (ft_strncmp(curr->var_name, "declare -x _=", 13))
                printf("%s\"%s\"\n", curr->var_name, curr->var_value);
            curr =(t_env_nodes *)curr->base.next;
        }
        return (0);
    }
    return (1);
}
