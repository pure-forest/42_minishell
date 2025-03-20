/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:44:56 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/19 12:44:56 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strndup(const char *s, size_t len)
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

