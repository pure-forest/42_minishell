/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:16:41 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:28:48 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_MEMCMP:
 * @DESCRIPTION: Compares 'n' bytes of memory area pointed to by strings 's1'
 		 and 's2'.
 * @PARAMETERS: 's1' - A pointer to the first memory area
 * 	        's2' - A pointer to the second memory area
 *	        'n' - The number of bytes to compare
 * @RETURN VALUE: (0) - If strings are the same OR
 		  (difference) between the two strings
 * @details:
 * unsigned char is used to handle non standard char characters/all possible
 * byte values
 * NULL POINTERS: Original 'memcmp' does not handle NULL pointers
 */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (i < n && str1[i] == str2[i])
		i++;
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}
