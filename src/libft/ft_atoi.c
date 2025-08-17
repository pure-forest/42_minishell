/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:46:09 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:07:47 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_ATOI:
 * @DESCRIPTION: Converts string (ascii characters) pointed to by 'str' to int.
 * @PARAMETER: 'str' - A pointer to the string to be modified.
 * @RETURN VALUE: The converted value or 0 if any errors.
 * @details:
 * OVER-/UNDER-FLOW: there is a check to handle this, and in that case return
 * value becomes LONG_MAX or LONG_MIN respectively.
 */

#include "libft.h"
#include <limits.h>

static int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	ft_issign(int neg, int *i, const char *str)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			neg = -1;
		(*i)++;
	}
	return (neg);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	res;

	i = 0;
	neg = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	neg = ft_issign(neg, &i, str);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res < 0 && neg == 1)
			return ((int)LONG_MAX);
		if (res < 0 && neg == -1)
			return ((int)LONG_MIN);
		i++;
	}
	return (res * neg);
}
