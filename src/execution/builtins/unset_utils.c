#include "../../../inc/execution.h"

int	is_equal_sign_present(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (SUCCESS);
	}
	return (FAIL);
}
