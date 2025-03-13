/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:09:39 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:45:07 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_PUTNBR_FD:
 * @DESCRIPTION: Sends 'n' (num) to the fd received as integer/value.
 * @PARAMETER: 'n' - The number to be written out to the fd.
 * 	       'fd' - The file descriptor.
 * @RETURN VALUE: No return value
 * @details:
 * OVERFLOW: The function handles it by hardcoding the case of INT_MIN, as
 * to not encounter overflow when negating the number
 */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			n = -n;
			ft_putchar_fd('-', fd);
		}
		if (n > 9)
			ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd((n % 10 + 48), fd);
	}
}
