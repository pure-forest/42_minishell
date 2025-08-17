/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:04:53 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 20:14:20 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRLCAT:
 * @DESCRIPTION: Concatinates the null terminated string pointed by '*src' to
 * the end of null-terminated buffer '*dst' It makes sure the buffer is always
 * null-terminated and that there wasn't any truncation.
 * @PARAMETERS: '*src' - Pointer to the source string.
 * 		'*dst' - Pointer to destination buffer.
 *		'dstsize' - Size of destination buffer.
 * @RETURN VALUE:  The length of the concatinated string if enough size in buffer
 * NOT including the null-terminator. If size is smaller, then it returns size+
 * src to signal that there was not enough space in buffer.
 * @details:
 * If dstsize < dst_len then the dst string is not modified, and that is why
 * New_dst is equal to the original. Even if the dst size is big, the new string
 * should be null terminated after concatination.
 * dst_len + j + 1 -- makes sure that there is enough space for null terminator
 * Original does not handle NULL src & dst
 */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	j;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	j = 0;
	while (src[j] && ((dst_len + j + 1) < dstsize))
	{
		dst[dst_len + j] = src[j];
		j++;
	}
	dst[dst_len + j] = '\0';
	return (dst_len + src_len);
}
