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
