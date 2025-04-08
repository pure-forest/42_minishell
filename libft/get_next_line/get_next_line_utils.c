/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:28:10 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/31 16:15:26 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	int		index;
	char	*temp;
	size_t	length;

	index = 0;
	temp = (char *)s;
	if (s == 0)
		return (NULL);
	length = 0;
	while (s[length] != 0)
		length++;
	if (c == 0)
		return (&temp[length]);
	while (s[index] != (unsigned char)c && s[index] != 0)
		index++;
	temp = &temp[index];
	if (s[index] == 0)
		return (0);
	return (temp);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*buffer;
	int		index;

	index = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	buffer = (char *)malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!buffer)
		return (NULL);
	while (s1[index] != 0)
	{
		buffer[index] = s1[index];
		index++;
	}
	while (s2[index - ft_strlen_gnl(s1)] != 0)
	{
		buffer[index] = s2[index - ft_strlen_gnl(s1)];
		index++;
	}
	buffer[index] = 0;
	return (buffer);
}

size_t	ft_strlen_gnl(const char	*str)
{
	size_t	length;

	length = 0;
	if (str == NULL || *str == 0)
		return (0);
	while (str[length] != 0)
		length++;
	return (length);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*buffer;
	int		index;

	index = 0;
	buffer = (char *)malloc(ft_strlen_gnl(s) + 1 * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (s[index] != 0)
	{
		buffer[index] = s[index];
		index++;
	}
	buffer[index] = 0;
	return (buffer);
}

char	*substr_and_free(char *s, unsigned int start, size_t len)
{
	char			*buffer;
	unsigned int	index;

	index = start;
	if (!s)
		return (NULL);
	if (start >= ft_strlen_gnl(s))
		len = 0;
	buffer = (char *)malloc((len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	else
	{
		while (index < len + start && s[index] != 0)
		{
			buffer[index - start] = s[index];
			index++;
		}
		buffer[index - start] = 0;
	}
	free(s);
	s = NULL;
	return (buffer);
}
