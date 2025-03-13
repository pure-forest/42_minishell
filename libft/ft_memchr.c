/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:24:11 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:28:17 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_MEMCHR:
 * @DESCRIPTION: Searches for the first occurrence of the character 'c' in the
 * first 'n' bytes of the memory area pointed to by 's'
 * @PARAMETERS: 's' - A pointer to the memory area
 * 	        'c' - The character to be searched/found
 *	        'n' - The number of bytes to search
 * @RETURN VALUE: A pointer to the first occurence of 'c' or null if not found
 * @details:
 * unsigned char is used to handle non standard char characters/all possible
 * byte values
 * Original 'memchr' does not handle NULL pointers
 */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;

	str = (unsigned char *) s;
	ch = (unsigned char) c;
	while (n--)
	{
		if (ch == *str)
			return ((void *)str);
		str++;
	}
	return (0);
}
