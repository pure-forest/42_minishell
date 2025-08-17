/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:45:07 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/26 17:34:55 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRCHR:
 * @DESCRIPTION: Looks for the first occurrence of the character 'c' in the
 * null-terminated string pointed to by 's'.
 * @PARAMETERS: 's' - The pointer to the null-terminated string.
 * 				'c' - The character to search for.
 * @RETURN VALUE:  A pointer to first occurrence of 'c' in the string or a
 * or a NULL pointer if not found.
 * @details:
 * SIZET: type of variable that can contain only non-negative values
 * NULL Pointer: The original function does not handle NULL
 */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (c == '\0' && c == *(s + 1))
			return ((char *)(s + 1));
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (0);
}
