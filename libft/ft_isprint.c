/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:59:09 by gboggion          #+#    #+#             */
/*   Updated: 2024/10/30 15:19:22 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                               FT_ISPRINT:
* @Description: Verifies if passed character 'c' is printable
* @Parameter: c - Character the function checks
* @Return value: (1) if c is printable -- (0) if not
**/

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
