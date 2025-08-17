/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:40:03 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/21 19:29:50 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_SUBSTR:
 * @DESCRIPTION: Creates a substring (&allocates memory for it via malloc) of
 * string 's', which starts from index 'start' for a max of 'len'.
 * @PARAMETERS: 's' - The source string from which the substring is created.
 * 		'start' - The index of string 's' from which new string starts
 		'len' - Maximum lenght of the new substring
 * @RETURN VALUE: A pointer to the new substring if everything is succesful
 		  If not it returns NULL (both in case malloc fails and if
 		  string is NULL.
 * @details:
 * NULL STRING: As these are additional functions, I decided to handle it
 */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	n;
	size_t	i;

	if (s)
	{
		i = 0;
		n = ft_strlen(s);
		if (start >= n)
			return (ft_strdup(""));
		if (n == 0)
			return ((char *) s);
		if ((n - start) < len)
			len = n - start;
		str = malloc(sizeof(char) * len + 1);
		if (!str)
			return (NULL);
		while (len--)
			str[i++] = s[start++];
		str[i] = 0;
		return (str);
	}
	return (0);
}
