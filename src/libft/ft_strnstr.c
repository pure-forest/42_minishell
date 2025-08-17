/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:17:31 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 20:17:35 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRNSTR:
 * @DESCRIPTION: Finds first occurence of null-terminated string 'little' in
 * the string 'big', 'len' amount of characters are checked
 * @PARAMETERS: 's' - The pointer to string.
 * 				'c' - The character to search.
 * @RETURN VALUE:  A pointer to last occurrence of 'c' or a NULL pointer
 * if not found.
 * @details:
 * NULL STRING: Original strnstr does not handle NULL STRING
 */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] && big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (0);
}
