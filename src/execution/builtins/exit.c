#include "../../../inc/execution.h"

int		is_all_numeric(char *arg);
long	ft_atol(const char *s);
int		count_args(char **arr);

int	ft_exit(t_struct_ptrs *data)
{
	long	code;
	int		arg_count;

	arg_count = count_args(data->input->cmd_arr);
	if (arg_count == 1)
		exit (data->exit_code);
	if (is_all_numeric(data->input->cmd_arr[1]) == NO)
	{
		set_exit_code(data, 255);
		ft_putstr_fd("exit\nexit", 2);
		print_error(data->input->cmd_arr[1], ": numeric argument required");
		exit(data->exit_code);
	}
	if (arg_count > 2)
	{
		set_exit_code(data, 4);
		ft_putstr_fd("exit\n", 2);
		print_error("exit: too many arguments", NULL);
		return (FAIL);
	}
	code = ft_atol(data->input->cmd_arr[1]);
	exit(code % 256);
}

int	count_args(char **arr)
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

int	is_all_numeric(char *arg)
{
	int	i;

	i = -1;
	if(arg)
	{
		while (arg[++i])
		{
			if (!ft_isdigit(arg[i]))
				return (NO);
		}
		return (YES);
	}
	return (NO);
}

long	ft_atol(const char *s)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s[i] && (s[i] == '-' || s[i] == '+'))
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		res = (res * 10) + (s[i++] - '0');
	return (res * sign);
}
