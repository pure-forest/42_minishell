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