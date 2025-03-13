/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:42:18 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:40:35 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_PUTCHAR_FD:
 * @DESCRIPTION: Sends 'c' to the specified (as arg) file descriptor.
 * @PARAMETER: 'c' - The character to send.
 *	       'fd' - The file descriptor.
 * @RETURN VALUE: No return value
 */

#include "libft.h"
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
