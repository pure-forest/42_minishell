#include "../../inc/execution.h"

void	print_error(char *var, char *str);

// void	print_err_exe(t_input *curr, t_exec_mem *mem, int err)
void	print_err_exe(t_struct_ptrs *data, char *cmd, int err)
{
	if (err == 1)
		perror(PROMPT);
	if (err == 2)
	{
		if (data->exit_code == 126)
			print_error(cmd, ": Permission denied");
		else
			print_error(cmd, ": No such file or directory");
	}
}

void	print_error(char *var, char *str)
{
	ft_putstr_fd(PROMPT, 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	close_fd(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

int	get_errno_codes(int err)
{
	if (err == ENOENT) // No such file or directory
		return (127);
	if (err == EACCES) // Permission denied
		return (126);
	return (1);
}

void	set_exit_code(t_struct_ptrs *data, int err)
{
	data->exit_code = get_errno_codes(err);
}
