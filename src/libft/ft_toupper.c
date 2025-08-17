/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:09:06 by gboggion          #+#    #+#             */
/*   Updated: 2024/11/04 11:44:33 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                               FT_TOUPPER:
 * @Description: Converts a lowercasee character 'c' (passed as integer) to 
 * uppercase. If the argument is other than a lowercaase alphabet, the same 
 * character that is passed to the function is returned.
 * @Parameter: c - Character to be converted if necessary.
 * @Return value:  The character 'c' converted to uppercase, otherwise if 
 * condition isn't met it returns 'c'.
 * @details:
 * INFO: - 32 is used to move character 'c' from its current position in the 
 * ASCII table to its equivalent uppercase position.
**/

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}
