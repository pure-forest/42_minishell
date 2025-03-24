/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:43:53 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/06 09:43:53 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include "../libft/libft.h"
# include "parsing.h"
# include "execution.h"
# include "lexer.h"

# define PINK "\033[1;38;5;218m"
# define BLUE "\033[1;34m"
# define END "\033[0m"
# define PROMPT PINK "🐱 --Catshell > " END


#endif
