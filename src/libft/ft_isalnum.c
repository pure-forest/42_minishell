/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:23 by gboggion          #+#    #+#             */
/*   Updated: 2024/10/29 18:45:37 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                               FT_ISALNUM:
* @Description: Verifies if character 'c' is alphabetical or numerical
* @Parameter: ch - Character the function checks
* @Return value: (8) if c is alphabetical or digit -- (0) if not
**/

#include "libft.h"

int	ft_isalnum(int ch)
{
	if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z'))
		return (8);
	else if (ch >= 'A' && ch <= 'Z')
		return (8);
	return (0);
}
