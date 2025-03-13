/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:09:06 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/04 11:43:37 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                               FT_TOLOWER:
 * @Description: Converts an uppercase character 'c' (passed as integer) to 
 * lowercase. If the argument is other than an uppercase alphabet, the same 
 * character that is passed to the function is returned.
 * @Parameter: c - Character to be converted if necessary.
 * @Return value:  The character 'c' converted to lowercase, otherwise if 
 * condition not met it returns 'c'.
 * @details:
 * INFO: + 32 is used to move character 'c' from its current position in the 
 * ASCII table to its equivalent lowercase position.
**/

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
