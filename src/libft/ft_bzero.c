/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:21:17 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:19:25 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_BZERO:
 * @DESCRIPTION: Converted to NULLs ('\0') the first 'n' characters of memory
 * pointed to by 's'
 * @PARAMETER: 's' - A pointer to the memory to be changed
 * 	       'n' - The number of bytes to be modified
 * @RETURN VALUE: NONE
 * @details:
 * SIZE_T: this makes sure that value of 'n' will not be negative and can
 * handle big values
 */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*p;

	p = (char *)s;
	i = 0;
	while (n--)
		p[i++] = 0;
}
