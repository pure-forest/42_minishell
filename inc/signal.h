/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:18:14 by ydeng             #+#    #+#             */
/*   Updated: 2025/04/26 17:18:16 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell.h"
# include "structure.h"

int		signal_init(void);
int		signal_init_heredoc(void);
int		signal_init_interrupt(t_struct_ptrs *data);
int		signal_init_child_process(void);
int		signal_init_parent_process(void);
void	handle_sigquit(void);

#endif
