/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:09:32 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/21 19:31:11 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_SPLIT:
 * @DESCRIPTION: Allocates an ARRAY of strings that is a result of dividing the
 		 string 's' into substrings according to the character 'c'
 		 deliminator
 		 The created array MUST END in NULL.
 * @PARAMETERS: 's' - String to be split up.
 		'c' - Deliminator, what determines the split of the string
 * @RETURN VALUE: (New Array of strings) - if all successfull
 		  (NULL) - if any errors or string is empty
 * @details:
 * NULL STRING: These are non library functions, so I decided to handle it
 * HELPER FUNCS: + FT_WORDCOUNT: To determine how big the array should be
		 + FT_STRNDUP: To duplicate the string into the specified array
		               element
		 + FT_FREEUP: Function to free up space in case any of the memory
		              allocation for the array fails
		 + FT_CREATE_ARRAY: Creates the array and its elements
 */
#include "libft.h"
#include <stdlib.h>

static int	ft_wordcount(const char *s, char delimiter)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == delimiter)
			i++;
		if (s[i] != 0 && s[i] != delimiter)
			count++;
		while (s[i] && s[i] != delimiter)
			i++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	str = (char *) malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!str)
		return (NULL);
	while (s[i] && i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static void	ft_freeup(char **array, int k)
{
	while (k >= 0)
		free (array[k--]);
	free (array);
}

static char	**ft_create_array(char **array, const char *s, int i, int delimiter)
{
	int	start_idx;
	int	k;

	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == delimiter)
			i++;
		start_idx = i;
		while (s[i] && s[i] != delimiter)
			i++;
		if (start_idx < i)
		{
			array[k] = ft_strndup(s + start_idx, i - start_idx);
			if (!array[k])
				return (ft_freeup(array, k), NULL);
			k++;
		}
	}
	array[k] = NULL;
	return (array);
}

char	**ft_split(char const *s, char delimiter)
{
	int		i;
	char	**array;
	char	**result;

	if (!s)
		return (NULL);
	i = 0;
	array = malloc(sizeof(char *) * ((ft_wordcount(s, delimiter) + 1)));
	if (array == NULL)
		return (NULL);
	result = ft_create_array(array, s, i, delimiter);
	if (!result || !result[0])
		return (NULL);
	return (array);
}
