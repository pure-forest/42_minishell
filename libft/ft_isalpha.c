/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:49:26 by gboggion          #+#    #+#             */
/*   Updated: 2024/10/29 16:00:44 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                               FT_ISALPHA:
* @Description: Verifies if passed character 'c' is alphabetical
* @Parameter: c - Character the function checks
* @Return value: (1024) if c is alphabetical -- (0) if not
**/

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1024);
	return (0);
}
