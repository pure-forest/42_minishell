/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:27:46 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/31 16:16:17 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	extract_new_line(char **ret_str, char *buffer)
{
	size_t	index;
	size_t	length;
	size_t	needle;

	index = 0;
	length = 0;
	needle = 0;
	while ((*ret_str)[needle] != '\n' && (*ret_str)[needle] != 0)
		needle++;
	if ((*ret_str)[needle] == 0)
		return ;
	length = ft_strlen_gnl(&(*ret_str)[needle + 1]);
	while (index < length)
	{
		buffer[index] = (*ret_str)[needle + 1];
		index++;
		needle++;
	}
	buffer[index] = 0;
	*ret_str = substr_and_free((*ret_str), 0, (needle - index + 1));
}

static void	free_and_join(char **ret_str, char *buffer)
{
	char	*temp_buffer;

	temp_buffer = ft_strjoin_gnl(*ret_str, buffer);
	if (temp_buffer == NULL)
	{
		free(*ret_str);
		*ret_str = NULL;
		return ;
	}
	free(*ret_str);
	*ret_str = temp_buffer;
}

static void	read_file(char **ret_str, char *buffer, int fd)
{
	int		byte_read;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(*ret_str);
			*ret_str = NULL;
			return ;
		}
		buffer[byte_read] = 0;
		free_and_join(&(*ret_str), buffer);
		if (ft_strchr_gnl(buffer, '\n'))
			return ;
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*ret_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret_str = ft_strdup_gnl(buffer);
	if (ret_str == NULL)
		return (NULL);
	if (ft_strchr_gnl(buffer, '\n') == 0)
		read_file(&ret_str, buffer, fd);
	if (ret_str == 0 || *ret_str == 0)
	{
		free(ret_str);
		ret_str = NULL;
		return (NULL);
	}
	extract_new_line(&ret_str, buffer);
	return (ret_str);
}
