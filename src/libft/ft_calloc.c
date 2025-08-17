/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:20:03 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/21 19:32:43 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                            FT_CALLOC:
 * @DESCRIPTION: Dynamically allocates memory for an array AND initializes
 * all allocated bytes to ZERO. The difference with malloc: malloc leaves
 * memory uninitialized
 * @PARAMETER: 'nmemb' - The number of elements in the array
 	       'size' - The size of each element
 * @RETURN VALUE: A pointer to the allocated memory, or a null pointer if the
 * request fails.
 * @details:
 * OVERFLOW: Is handled by checking before memory allocation by using the max
 * value of size_t (SIZE_MAX), this allows to see the maximum value size can
 * have. We also check if nmemb IS NOT zero, as there is no risk of overflow
 */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*c_tmp;
	size_t	i;
	size_t	tot_size;

	if (nmemb && size > (SIZE_MAX / nmemb))
		return (NULL);
	tot_size = nmemb * size;
	c_tmp = malloc (tot_size);
	if (!c_tmp)
		return (NULL);
	i = 0;
	while (i < tot_size)
		c_tmp[i++] = 0;
	return (c_tmp);
}
