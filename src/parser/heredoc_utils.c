#include "../../inc/parsing.h"

char	*ft_rejoin_str(char **words);

int	check_for_expansion(t_struct_ptrs *data, char **new_line)
{
	char	**words;
	int		i;

	if (!ft_strchr(*new_line, '$'))
		return (SUCCESS);
	words = ft_split(*new_line, ' ');
	i = 0;
	if (!words)
		return (FAIL);
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = expand_variable(data, words[i]);
			if (!words[i])
				return (FAIL);
		}
		i++;
	}
	free(*new_line);
	*new_line = ft_rejoin_str(words);
	if (*new_line)
		return (SUCCESS);
	return (FAIL);
}

char	*ft_rejoin_str(char **words)
{
	char	*str;
	char	*temp;
	int		i;

	temp = NULL;
	if (!words || !words[0])
		return (NULL);
	i = 1;
	str = ft_strdup(words[0]);
	while (words[i])
	{
		temp = ft_strjoin(str, " ");
		free(str);
		str = ft_strjoin(temp, words[i]);
		free(temp);
		i++;
	}
	ft_free_double_ptr(words);
	return (str);
}
