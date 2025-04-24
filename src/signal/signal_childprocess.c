#include "../../inc/signal.h"

static void	handle_child_sigquit_as_default(void);
static void	signal_handler_child(int signum, siginfo_t *info, void *context);

int	signal_hanging_init(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		return (FAIL);
	handle_child_sigquit_as_default();
	sa.sa_sigaction = signal_handler_child;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL))
		return (FAIL);
	else
		return (SUCCESS);
}

int	parent_signal(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		return (FAIL);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) || sigaction(SIGQUIT, &sa, NULL))
		return (FAIL);
	else
		return (SUCCESS);
}

static void	signal_handler_child(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_child_sigquit_as_default(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	if (sigemptyset(&sa.sa_mask) == -1)
		return ;
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
