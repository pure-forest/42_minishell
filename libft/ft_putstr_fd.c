/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:51:58 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/05 11:06:42 by ydeng            ###   ########.fr       */
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
	if (s && fd >= 0)
	{
		write(fd, s, ft_strlen(s));
	}
	return ;
}
