#include "../../inc/signal.h"

static void	signal_handler(int signum, siginfo_t *info, void *context);

int	signal_init(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		return (FAIL);
	 sa.sa_sigaction = signal_handler;
	 sa.sa_flags = SA_SIGINFO;
	 sigaction(SIGINT, &sa, NULL);
	 sigaction(SIGQUIT, &sa, NULL);
	return (SUCCESS);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;

	if (signum == SIGINT || signum == SIGQUIT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		printf("catch signal failed\n");
}