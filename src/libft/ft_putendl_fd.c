/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:58:03 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/11 14:11:31 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_PUTENDL_FD:
 * @DESCRIPTION: Writes the string 's' to the file descriptor 'fd' followed by
 * a '\n' to make a new line
 * @PARAMETER: 's' - The string to write to the file descriptor.
 * 	       'fd' - The file descriptor.
 * @RETURN VALUE: No return value
 */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
		write(fd, "\n", 1);
	}
}
