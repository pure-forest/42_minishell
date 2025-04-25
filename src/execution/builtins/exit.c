#include "../../../inc/execution.h"

static int	count_args(char **arr);
static void	print_numeric_error(t_struct_ptrs *data, char *str_input, int code);
static void	clean_up_and_exit(t_struct_ptrs *data, t_input *curr, \
								t_exec_data *exec_data);

int	ft_exit(t_struct_ptrs *data, t_input *curr, t_exec_data *exec_data)
{
	long	code;
	int		arg_count;

	arg_count = count_args(curr->cmd_arr);
	if (arg_count == 1)
	{
		clean_up_and_exit(data, curr, exec_data);
		exit (data->exit_code);
	}
	if (is_valid_numeric_input(curr->cmd_arr[1]) == NO)
		print_numeric_error(data, curr->cmd_arr[1], 4);
	if (arg_count > 2)
	{
		set_exit_code(data, 4);
		ft_putstr_fd("exit\n", 2);
		print_error("exit: too many arguments", NULL, NULL);
		return (FAIL);
	}
	code = ft_atol(curr->cmd_arr[1]);
	if (code == -1)
		print_numeric_error(data, curr->cmd_arr[1], 4);
	clean_up_and_exit(data, curr, exec_data);
	exit(code % 256);
}

static void	clean_up_and_exit(t_struct_ptrs *data, t_input *curr, \
								t_exec_data *exec_data)
{
	handle_standard_fds(data, exec_data, YES);
	clean_up_exec_creations(data, curr);
	mega_clean(data);
}

static int	count_args(char **arr)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	if (arr)
	{
		while (arr[++i])
			count += 1;
	}
	return (count);
}

int	is_valid_numeric_input(char *arg)
{
	int	i;

	i = -1;
	if (arg)
	{
		while (arg[++i])
		{
			if (arg[i] == '+' || arg[i] == '-')
				continue ;
			if (!ft_isdigit(arg[i]))
				return (NO);
		}
		return (YES);
	}
	return (NO);
}

static void	print_numeric_error(t_struct_ptrs *data, char *str_input, int code)
{
	set_exit_code(data, code);
	ft_putstr_fd("exit\n", 2);
	print_error("exit: ", str_input, ": numeric argument required");
	exit(data->exit_code);
}
