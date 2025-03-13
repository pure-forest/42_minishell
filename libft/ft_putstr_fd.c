/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:51:58 by gboggion          #+#    #+#             */
/*   Updated: 2025/02/13 10:27:14 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_PUTSTR_FD:
 * @DESCRIPTION: Sends 's' pointer to the specified file descriptor.
 * @PARAMETER: 's' - The string to send.
 * 	       'fd' - The file descriptor.
 * @RETURN VALUE: No return value
 * @DETAILS: FD can only have positive values or 0
 */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s && fd >= 0)
	{
		while (s[i])
			write(fd, &s[i++], 1);
	}
	return ;
}
