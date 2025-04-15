#include "../../inc/signal.h"

static void	signal_handler(int signum, siginfo_t *info, void *context);
static void	handle_sigquit(void);


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
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_sigquit(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	if (sigemptyset(&sa.sa_mask) == -1)
		return ;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
