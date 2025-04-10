/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:29:39 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/10 14:12:37 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRLEN:
 * @DESCRIPTION: Calculates the length of the null-terminated string pointed to
 * by 's'
 * @PARAMETERS: '*s' - A pointer to the string '*s'
 * @RETURN VALUE: The length of the string in size_t type
 * @details:
 * SIZET: type of variable that can contain only non-negative values
 * NULL Pointer: The original function does not handle NULL
 */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
