/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_yutong.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:17:40 by ydeng             #+#    #+#             */
/*   Updated: 2025/04/26 17:17:40 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

char	*append_character_in_string(char *s1, char c)
{
	char	*s_new;
	int		i;
	int		j;

	if (s1 && c)
	{
		s_new = ft_calloc((ft_strlen(s1) + 1 + 1), sizeof(char));
		if (!s_new)
			return (print_error("Malloc failure", NULL, NULL),
				free((char *)s1), NULL);
		i = 0;
		j = 0;
		while (s1 && s1[j])
			s_new[i++] = s1[j++];
		s_new[i++] = c;
		s_new[i] = 0;
		return (free((char *)s1), s_new);
	}
	return (0);
}
