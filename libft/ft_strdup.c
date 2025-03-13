/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:41:58 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/17 19:51:19 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRDUP:
 * @DESCRIPTION: Duplicates string 's' into a new malloc assigned string 's'
 * @PARAMETERS: 'src' - Pointer to string to be copied.
 * @RETURN VALUE: A pointer to the new string
 * @details:
 * NULL STRING: Original 'strdup' does not handle it
 */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*s;
	char	*start;

	s = (char *) malloc (sizeof(char) * (ft_strlen((char *)src) + 1));
	if (!s)
		return (NULL);
	start = s;
	while (*src)
		*s++ = *src++;
	*s = 0;
	return (start);
}
