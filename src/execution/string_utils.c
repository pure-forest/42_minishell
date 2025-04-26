/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:30:25 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/26 17:30:25 by gboggion         ###   ########.fr       */
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

char	*ft_strjoin_and_free(char const *s1, char const *s2)
{
	char	*s_new;
	int		i;
	int		j;

	if (s1 && s2)
	{
		s_new = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
		if (!s_new)
			return (free((char *)s1), free((char *)s2), NULL);
		i = 0;
		j = 0;
		while (s1 && s1[i])
			s_new[i++] = s1[j++];
		j = 0;
		while (s2 && s2[j])
			s_new[i++] = s2[j++];
		s_new[i] = 0;
		free((char *)s1);
		s1 = NULL;
		free((char *)s2);
		s2 = NULL;
		return (s_new);
	}
	return (0);
}

long	ft_atol(const char *s)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s[i] && (s[i] == '-' || s[i] == '+'))
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		res = (res * 10) + (s[i++] - '0');
		if (res < 0 && sign == 1)
			return (-1);
		if (res < 0 && sign == -1)
			return (-1);
	}
	return (res * sign);
}
