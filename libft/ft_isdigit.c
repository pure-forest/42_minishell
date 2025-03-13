/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:53:04 by gboggion          #+#    #+#             */
/*   Updated: 2024/10/29 18:03:55 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**                               FT_ISDIGIT:
* @Description: Verifies if passed character 'c' is digit
* @Parameter: c - Character the function checks
* @Return value: (1) if c is digit -- (0) if not
**/

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
