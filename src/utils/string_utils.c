#include "../../inc/utils.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strndup(const char *s, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	str = (char *) malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!str)
		return (NULL);
	while (s[i] && i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoin_and_free(char const *s1, char const *s2)
{
	char	*s_new;
	int		i;
	int		j;

	if (s1 && s2)
	{
		s_new = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
		if (!s_new)
			return (free((char *)s1), free((char *)s2), NULL);
		i = 0;
		j = 0;
		while (s1 && s1[i])
			s_new[i++] = s1[j++];
		j = 0;
		while (s2 && s2[j])
			s_new[i++] = s2[j++];
		s_new[i] = 0;
		return (free((char *)s1), free((char *)s2), s_new);
	}
	return (0);
}

char *append_character_in_string(char *s1, char c)
{
	char	*s_new;
	int		i;
	int		j;

	if (s1 && c)
	{
		s_new = ft_calloc((ft_strlen(s1) + 1 + 1), sizeof(char));
		if (!s_new)
			return (free((char *)s1), NULL);
		i = 0;
		j = 0;
		while (s1 && s1[i])
			s_new[i++] = s1[j++];
		s_new[i++] = c;
		s_new[i] = 0;
		return (free((char *)s1), s_new);
	}
	return (0);
}
