/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:16:03 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 17:27:40 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRRCHR:
 * @DESCRIPTION: Looks for the last occurrence of the character 'c' in the
 * null-terminated string pointed to by 's'.
 * @PARAMETERS: 's' - The pointer to string.
 * 				'c' - The character to search.
 * @RETURN VALUE:  A pointer to last occurrence of 'c' or a NULL pointer
 * if not found.
 * @details:
 * NULL STRING: Original strrchr does not handle NULL STRING
 */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	length;

	length = ft_strlen(str);
	if (c == 0)
		return ((char *)(str + length));
	while (length >= 0)
	{
		if (str[length] == c)
			return ((char *)(str + length));
		length--;
	}
	return (0);
}
