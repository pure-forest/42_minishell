# include "../../inc/expansion.h"

char	*expand_variable(t_struct_ptrs *data, char *src)
{
	char	*new_value;
	char	*extra;
	char	*needle;

	new_value = NULL;
	extra = NULL;
	if (!src || !*src)
		return (NULL);
	needle = ft_strjoin(ft_strchr(src, '$') + 1, "=");
	printf("needle = %s\n", needle);
	if (ft_strlen(needle) != (ft_strlen(src) - 1))
	{
		extra = ft_calloc((src - needle), sizeof(char));
		ft_strlcat(extra, src, (src - needle));
	}
	while (data->env)
	{
		if (!ft_strncmp(needle, data->env->var_name, ft_strlen(needle)))
		{
			printf("are we here?\n");
			new_value = ft_strdup(data->env->var_value);
			printf("expand value = %s\n", new_value);
			if (!new_value)
				return (NULL);
			if (extra)
				return (free_and_join(extra, new_value));
			return (new_value);
		}
		data->env = (t_env_nodes *)(data->env->base.next);
	}
	return (NULL);
}

