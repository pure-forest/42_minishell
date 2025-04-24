#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell.h"
# include "structure.h"

int		signal_init(void);
int		signal_init_heredoc(void);
int		signal_hanging_init(void);
void	handle_sigquit(void);
int		parent_signal(void);
int	interupt_input(t_struct_ptrs *data);

#endif
