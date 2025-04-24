#include "../../inc/signal.h"

static void	signal_handler(int signum, siginfo_t *info, void *context);

int	signal_init(void)
{
	struct sigaction	sa;

	handle_sigquit();
	ft_memset(&sa, 0, sizeof(struct sigaction));
	if (sigemptyset(&sa.sa_mask) == -1)
		return (FAIL);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (FAIL);
	return (SUCCESS);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		g_signal_numb = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	if (sigemptyset(&sa.sa_mask) == -1)
		return ;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

int	interupt_input(t_struct_ptrs *data)
{
	if (g_signal_numb == SIGINT)
	{
		g_signal_numb = 0;
		data->exit_code = 130;
		return (SUCCESS);
	}
	return (SUCCESS);
}
