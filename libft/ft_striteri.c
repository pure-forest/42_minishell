/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:09:18 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:52:46 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRITERI:
 * @DESCRIPTION: Applies a defined function 'f' on EVERY character of string 's'
 		 Giving to 'f' the params: (index of each character) and
 		 (address of each character) to be modified.
 * @PARAMETERS: 's' - The string on which to operate.
 * 		'f' - The function to apply on each charcter.
 * @RETURN VALUE: NONE
 * @details:
 * NULL STRING: As these are additional functions, I decided to handle it
 */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
