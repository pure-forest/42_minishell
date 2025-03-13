/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:48:24 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 20:18:00 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRLCPY:
 * @DESCRIPTION: Copies 'dsstsize' amount of characters of n-term. string  '*src'
 * to buffer '*dst', same as ft_strlcat it ensures that buffer is always
 * null-terminated and that there wasn't any truncation.
 * @PARAMETERS: '*src' - Pointer to the source string.
 * 		'*dst' - Pointer to destination buffer.
 *		'dstsize' - Size of destination buffer.
 * @RETURN VALUE:  No matter if copying was truncated or not it returns the
 * length of the source string without including null-terminator.
 * @details:
 * NULL src string is NOT handled by original strlcpy
 */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize > src_len + 1)
		ft_memcpy(dst, src, src_len + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	return (src_len);
}
