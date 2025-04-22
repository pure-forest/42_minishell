#include "../../inc/signal.h"

static void		signal_handler_heredoc(int signum, siginfo_t *info,
					void *context);
static void		signal_handler_hanging(int signum, siginfo_t *info,
					void *context);

sig_atomic_t	g_signal_numb;

int	signal_init_heredoc(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		return (FAIL);
	handle_sigquit();
	sa.sa_sigaction = signal_handler_heredoc;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (FAIL);
	return (SUCCESS);
}

int	signal_hanging_init(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		return (FAIL);
	sa.sa_sigaction = signal_handler_hanging;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) || sigaction(SIGQUIT, &sa, NULL))
		return (FAIL);
	else
		return (SUCCESS);
}

static void	signal_handler_heredoc(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		g_signal_numb = SIGINT;
		close(STDIN_FILENO);
		write(1, "\n", 1);
	}
}

static void	signal_handler_hanging(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT || signum == SIGQUIT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
}
