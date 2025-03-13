/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:10:05 by gboggion          #+#    #+#             */
/*   Updated: 2025/02/13 10:22:52 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_MEMMOVE:
 * @DESCRIPTION: Works similarly to memcp; copying 'n' bytes from 'src' to 'dst'
				 However, memmove considers memory overlap and makes sure the
				 copying works regardless.
 * @PARAMETERS: 'src' - A pointer to the source memory area
 * 	      		'dst' - A pointer to the destination memory area
 *	        	'n' - The number of bytes to copy
 * @RETURN VALUE: A pointer to the newly copied destination memory area
 * @details:
	NULL POINTERS: The original 'memmove' does not handle them, but I have
	OVERFLOW: The original does not handle it
 */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (!dst || !src)
		return (NULL);
	d = (char *) dst;
	s = (char *) src;
	if (dst <= src)
		ft_memcpy(dst, src, n);
	if (dst > src)
	{
		while (n--)
			d[n] = s[n];
	}
	return (d);
}
