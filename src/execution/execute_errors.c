#include "../../inc/execution.h"

void	print_err_exe(t_struct_ptrs *data, char *cmd, int err)
{
	if (err == 1)
		perror(PROMPT);
	if (err == 2 || err == 3 || err == 4)
	{
		if (data->exit_code == 126 && err != 4)
			print_error(cmd, NULL, ": Permission denied");
		if ((data->exit_code == 127 && err == 2) || (data->exit_code == 126 && err == 4) || (data->exit_code == -1))
			print_error(cmd, NULL, ": No such file or directory");
		if (data->exit_code == 127 && err == 3)
			print_error(cmd, NULL, ": command not found");
	}
}

void	print_error(char *var, char *var_2, char *str)
{
	ft_putstr_fd("catshell: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(var_2, 2);
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
	if (err == 6)
		return (1);
	if (err == SUCCESS)
		return (0);
	if (err == ENOENT) // No such file or directory
		return (127);
	if (err == EACCES) // Permission denied
		return (126);
	if (err == 3)
		return (-1);
	if (err == 4)
		return (2);
	// if (err == 255)	//DELETE?????
	// 	return (255);
	return (1);
}

void	set_exit_code(t_struct_ptrs *data, int err)
{
	data->exit_code = get_errno_codes(err);
}
