/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:39:02 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 15:04:12 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_MEMCPY:
 * @DESCRIPTION: Copies 'n' bytes from the memory area´'src', into the area
				 pointed to by 'dest'.
 * @PARAMETERS: 'dest' - A pointer to the destination memory area
  	       	    'src' - A pointer to the source memory area
				'n' - The number of bytes to copy
 * @RETURN VALUE: A pointer to the destination mem area
 * @details:
	CAST: Since it is void pointers this makes sure the memory is filled with
		  the desired value
	NULL POINTERS: The original 'memcpy' does not handle them, so neither did I
	OVERFLOW: The original does not handle it
 */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			pos;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	pos = 0;
	while (n--)
	{
		d[pos] = s[pos];
		pos++;
	}
	return (d);
}
