#include "../../inc/expansion.h"

bool is_valid_expandable(char c)
{
	if (c == 0)
		return (NO);
	if (ft_isalnum(c) || ft_isalpha(c) || c == '_')
		return (YES);
	else
		return (NO);
}

bool should_just_append(char c, char *src)
{
	int	i;

	i = 0;
	if (c != '$')
		return (YES);
	else if (c == '$' && is_valid_expandable(src[i + 1]) == NO)
		return (YES);
	else
		return (NO);
}

bool is_special_expansion_case(char *src)
{
	if (!ft_strncmp(src, "$", ft_strlen(src)))
		return (YES);
	if (!ft_strncmp(src, "$?", ft_strlen(src)))
		return (YES);
	return (NO);
}

char	*handle_special_expansion(t_struct_ptrs *data, char *src)
{
	(void)data;
	if (!ft_strncmp(src, "$", ft_strlen(src)))
		return (src);
	else if (!ft_strncmp(src, "$?", ft_strlen(src)))
	{
		printf("Handle exit code to be done\n");
		return (src);
	}
	return (NULL);
}