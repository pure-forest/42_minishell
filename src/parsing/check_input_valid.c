/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:38:26 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/08 19:58:27 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"


int	check_valid_input(int argc, char *argv[])
{
	if (argc != 2)
		return(printf("input only 1 argument\n"));
	else
		return(printf("%s\n", argv[1]));
}
