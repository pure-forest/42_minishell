/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:28:26 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 20:18:48 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRTRIM:
 * @DESCRIPTION: Allocates memory for new string, copies in 's1' EXCLUDING the
 * 		 the characters specified in 'set' from the beginning and end.
 * @PARAMETERS: 's1' - String to be trimmed.
 * 		'set' - The characters to trim.
 * @RETURN VALUE: (new trimmed string) - if everything is successfull
 		  (NULL) in case there is errors
 * @details:
 * NULL STRING: As these are additional functions, I decided to handle it
 * FT_STRLEN: used to calulate length of string
 * FT_STRCHR: Set is sent as string, and first occurence character to find is
	      the string 's1' current index character 's1[i]'
	      Same thing is done for the j index (representing the end of string)
 * J - 1 - This is to account for zero-based indexing
 * FT_STRLCPY: Copies the portion of string trimmed into the new string
 */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*new;

	new = 0;
	if (s1 && set)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && j > i && ft_strchr(set, s1[j - 1]))
			j--;
		new = (char *) malloc((j - i + 1) * sizeof(char));
		if (new)
			ft_strlcpy(new, &s1[i], (j - i + 1));
	}
	return (new);
}
