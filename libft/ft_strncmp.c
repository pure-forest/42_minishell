/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:09:11 by gboggion          #+#    #+#             */
/*   Updated: 2025/02/13 10:30:50 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_STRNCMP:
 * @DESCRIPTION: Compares the first 'n' characters of strings 's1' and 's2'
 * @PARAMETERS: 's1' - Pointer to first null-termin. string.
 * 		's2' - Pointer to second null-termin. string.
 * 		'n' - The maximum amount of characters to compare.
 * @RETURN VALUE: (0) when n is zero or when the strings are the same
 		  (<0) when s1 < s2, i.e. string is smaller
 		  (>0) when s2 > s2, i.e. string two is bigger
 * @details:
 * NULL STRING: Original 'strrchr' does not handle NULL STRING but after the
				project changed it to be robust
 */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (n <= 0 || s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
