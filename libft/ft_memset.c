/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:55:53 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:51:30 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_MEMSET:
 * @DESCRIPTION: Sets the first 'n' bytes of the memory area of 'dst' with the
				 byte passed in 'c'.
 * @PARAMETERS: 'dst' - A pointer to the memory area
 * 	        	'c' - The value to be used to fill the bytes
 *	      		'len' - The number of bytes to be changed
 * @RETURN VALUE: A pointer to the changed 'dst' memory area
 * @details:
	NULL POINTERS: The original 'memset' does not handle them, so neither did I
	OVERFLOW: The original does not handle it
 */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t len)
{
	size_t	i;
	char	*p;

	p = (char *)dst;
	i = 0;
	while (len--)
		p[i++] = c;
	return (dst);
}
