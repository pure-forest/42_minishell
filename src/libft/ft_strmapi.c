/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:34 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 20:16:56 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRMAPI:
 * @DESCRIPTION: Applies a defined function 'f' on EVERY character of string 's'
 		 Giving to 'f' the params: (index of each character) and
 		 (character itself) to be modified.
 		 Then allocates (malloc) and creates the new string.
 * @PARAMETERS: 's' - The string on which to operate.
 * 		'f' - The function to apply on each charcter.
 * @RETURN VALUE: (New string) - created after applying 'f'.
 		  (NULL) - in case of errors.
 * @details:
 * NULL STRING: As these are additional functions, I decided to handle it
 */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	if (!s || !f)
		return (NULL);
	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}
