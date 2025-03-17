/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:58:18 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/16 20:58:18 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void sort_export(t_struct_ptrs *data)
{
	t_export	*curr;
	int         smallest;

	curr = data->export;
	while ()
}

void	set_smallest(t_export *export)
{
	int	smallest;
	
	smallest = 127;
	while (curr && (curr = curr->next))
    {
        if (curr->first_letter < smallest)
            curr->smallest = 1;
    }
}