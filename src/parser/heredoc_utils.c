#include "../../inc/parsing.h"

static char	*ft_rejoin_str(char **words);
static int	handle_not_valid_expansion(char **new_line);

int	check_for_expansion(t_struct_ptrs *data, char **new_line)
{
	char	**words;
	int		i;

	if (!ft_strchr(*new_line, '$') || ft_strchr(*new_line, '\'')
		|| ft_strchr(*new_line, '\"'))
		return (SUCCESS);
	words = ft_split(*new_line, ' ');
	if (!words)
		return (print_error("Malloc failure", NULL, NULL), FAIL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = expand_variable(data, words[i]);
			if (!words[i])
				return (handle_not_valid_expansion(new_line));
		}
		i++;
	}
	free(*new_line);
	*new_line = ft_rejoin_str(words);
	if (*new_line)
		return (ft_free_double_ptr(words), SUCCESS);
	return (ft_free_double_ptr(words), FAIL);
}

char	*generate_heredoc_name(void)
{
	static int	index;
	char		*number_str;
	char		*file_name;

	number_str = ft_itoa(index);
	if (!number_str)
		return (NULL);
	file_name = ft_strjoin(HEREDOC_TEMP_NAME, number_str);
	if (!file_name)
		return (free(number_str), NULL);
	while (access(file_name, F_OK) == 0)
	{
		free(number_str);
		free(file_name);
		index++;
		number_str = ft_itoa(index);
		if (!number_str)
			return (NULL);
		file_name = ft_strjoin(HEREDOC_TEMP_NAME, number_str);
		if (!file_name)
			return (free(number_str), NULL);
	}
	free(number_str);
	index++;
	return (file_name);
}

static char	*ft_rejoin_str(char **words)
{
	char	*str;
	char	*temp;
	int		i;

	if (!words || !words[0])
		return (NULL);
	i = 1;
	temp = NULL;
	str = ft_strdup(words[0]);
	if (!str)
		return (print_error("Malloc failure", NULL, NULL), NULL);
	while (words[i])
	{
		temp = ft_strjoin(str, " ");
		free(str);
		if (!temp)
			return (print_error("Malloc failure", NULL, NULL), NULL);
		str = ft_strjoin(temp, words[i]);
		if (!str)
			return (print_error("Malloc failure", NULL, NULL), NULL);
		i++;
	}
	return (str);
}

void	write_into_temp_file(t_token *token, t_struct_ptrs *data, int fd,
					char **temp)
{
	if (token->expand_heredoc == YES)
	{
		if (check_for_expansion(data, temp) == FAIL)
			return ;
	}
	write(fd, *temp, ft_strlen(*temp));
	free(*temp);
	*temp = NULL;
	write(fd, "\n", 1);
}

static int	handle_not_valid_expansion(char **new_line)
{
	free(*new_line);
	*new_line = ft_strdup("");
	if (!*new_line)
		return (print_error("Malloc failure", NULL, NULL), FAIL);
	return (SUCCESS);
}
