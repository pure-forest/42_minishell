/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:17:51 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:54:57 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRJOIN
 * @DESCRIPTION: Allocates memory for new string 's_new' and then concatenates
 		 's1' and 's2' to it.
 * @PARAMETERS: 's1' - First string.
 * 		's2' - Second string.
 * @RETURN VALUE: (new concatenated string) - if everything is successfull
 		  (NULL) in case there is errors
 * @details:
 * NULL STRING: As these are additional functions, I decided to handle it
 */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_new;
	int		i;
	int		j;

	if (s1 && s2)
	{
		s_new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
		if (!s_new)
			return (NULL);
		i = 0;
		j = 0;
		while (s1[i])
			s_new[i++] = s1[j++];
		j = 0;
		while (s2[j])
			s_new[i++] = s2[j++];
		s_new[i] = 0;
		return (s_new);
	}
	return (0);
}
