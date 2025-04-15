#include "../../inc/signal.h"

static void	signal_handler_heredoc(int signum, siginfo_t *info, void *context);
sig_atomic_t signal_numb;

int	signal_init_heredoc(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		return (FAIL);
	sa.sa_sigaction = signal_handler_heredoc;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	return (SUCCESS);
}

static void	signal_handler_heredoc(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		signal_numb = 2;
		close(STDIN_FILENO);
		write(1, "\n", 1);
	}
}
