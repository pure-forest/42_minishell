#include "../../inc/parsing.h"

char	*ft_rejoin_str(char **words);

static	int	handle_not_valid_expansion(char **new_line)
{
	free(*new_line);
	*new_line = ft_strdup("");
	return (SUCCESS);
}

int	check_for_expansion(t_struct_ptrs *data, char **new_line)
{
	char	**words;
	int		i;

	if (!ft_strchr(*new_line, '$') || ft_strchr(*new_line, '\'') ||
		ft_strchr(*new_line, '\"'))
		return (SUCCESS);
	words = ft_split(*new_line, ' ');
	if (!words)
		return (FAIL);
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

char	*ft_rejoin_str(char **words)
{
	char	*str;
	char	*temp;
	int		i;

	if (!words || !words[0])
		return (NULL);
	i = 1;
	temp = NULL;
	str = ft_strdup(words[0]);
	while (words[i])
	{
		temp = ft_strjoin(str, " ");
		free(str);
		str = ft_strjoin(temp, words[i]);
		free(temp);
		i++;
	}
	return (str);
}
