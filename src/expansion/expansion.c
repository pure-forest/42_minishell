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
			// printf("after expansion = %s\n", new_value);
			if (!new_value)
				return (FAIL);
			node->value = new_value;
		}
		node = (t_token *)(node->base.next);
	}
	return (SUCCESS);
}

char	*expand_variable(t_struct_ptrs *data, char *src)
{
	char	*needle;

	if (!src || !*src)
		return (NULL);
	needle = ft_strjoin(ft_strchr(src, '$') + 1, "=");
	if (!needle)
		return (free(src), NULL);
	while (data->env)
	{
		if (!ft_strncmp(needle, data->env->var_name, ft_strlen(needle)))
			return (process_expanded_var(&src, &needle, data->env->var_value));
		data->env = (t_env_nodes *)(data->env->base.next);
	}
	free(needle);
	needle = NULL;
	free(src);
	src = NULL;
	return (NULL);
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
	if (!new_value)
		return (NULL);
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
