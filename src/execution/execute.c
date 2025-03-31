#include "../../inc/execution.h"

void	execute(t_struct_ptrs *data)
{
	if (!is_builtin(data))
	{
		data->exit_code = launch_builtiin(data);
		return ;
	}
}

