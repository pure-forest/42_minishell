#include "../../inc/expansion.h"

static char	*get_extra_before_dollar(char *src);
static char	*process_expanded_var(char **src, char **needle, char *var_value);

int	expand_word_token(t_struct_ptrs *data)
{
	t_token *node;
	char	*new_value;

	node = data->token;
	new_value = NULL;
	while (node)
	{
		if (ft_strchr(node->value, '$') && node->should_expand == YES)
		{
			new_value = expand_variable(data, node->value);
			if (!new_value)
				return (FAIL);
			// if (!*new_value)
			// {
				// free(new_value);
				// new_value = NULL;
			// 	return (SUCCESS);
			// }
			node->value = new_value;
		}
		node = (t_token *)(node->base.next);
	}
	return (SUCCESS);
}

char	*expand_variable(t_struct_ptrs *data, char *src)
{
	char	*needle;
	char	*pid;
	t_env_nodes	*curr;

	if (!src || !*src)
		return (NULL);
	curr = data->env;
	needle = ft_strjoin(ft_strchr(src, '$') + 1, "=");
	pid = ft_itoa(getpid());
	if (!pid)
		return (free(needle), free(src), NULL);
	if (!needle)
		return (free(src), NULL);
	while (curr)
	{
		if (!ft_strncmp(needle, "$=", 2))
			return (process_expanded_var(&src, &needle, pid));
		else if (!ft_strncmp(needle, curr->var_name, ft_strlen(needle)))
			return (free(pid), process_expanded_var(&src, &needle, curr->var_value));
		curr = (t_env_nodes *)curr->base.next;
	}
	return (free(pid), process_expanded_var(&src, &needle, ""));
}

static char	*process_expanded_var(char **src, char **needle, char *var_value)
{
	char	*new_value;
	char	*extra;

	extra = get_extra_before_dollar(*src);
	new_value = ft_strdup(var_value);
	free(*needle);
	*needle = NULL;
	free(*src);
	*src = NULL;
	if (!extra)
		return (new_value);
	else
		return (ft_strjoin_and_free(extra, new_value));
}

static char	*get_extra_before_dollar(char *src)
{
	int		length;
	int		i;
	char	*extra;

	i = 0;
	length = 0;
	while (src[length] != '$')
		length++;
	if (length == 0)
		return (NULL);
	extra = ft_calloc(length + 1, sizeof(char));
	if (!extra)
		return (NULL);
	while (src[i] != '$')
	{
		extra[i] = src[i];
		i++;
	}
	extra[i] = '\0';
	return (extra);
}
