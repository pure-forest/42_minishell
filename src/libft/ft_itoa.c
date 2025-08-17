/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:39:10 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:22:44 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_ITOA:
 * @DESCRIPTION: Generates a string that represents the int value received as an
 * argument using malloc(3). Negative numbers must be handled.
 * @param n The integer to be converted.
 * @RETURN VALUE: The string representing the number or null if the memory fails
 * @details:
 * OVERFLOW: by handling the INT_MIN directly it handles possible overflow if
 * trying to negate the INT_MAX directly
 * value becomes INT_MAX or INT_MIN respectively.
 */

#include "libft.h"
#include <stdlib.h>

int	ft_length(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_min_int(void)
{
	char	*str;
	char	*num;
	int		i;

	num = "-2147483648";
	i = 0;
	str = (char *) malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	while (num[i])
	{
		str[i] = num[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_num_handling(char *str, int n, int len)
{
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == -2147483648)
		return (ft_min_int());
	len = ft_length(n);
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	return (ft_num_handling(str, n, len));
}
