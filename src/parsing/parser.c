#include "../../inc/parsing.h"

t_cmd_table	*cmd_table_init(char **cmd_args)
{
	t_cmd_table *temp;

	temp = ft_calloc(1, sizeof(t_cmd_table *));
	if (!temp)
		return (NULL);
	temp = (t_cmd_table *){0};
	
}

t_cmd_table *parser(t_token *token_list)
{

}
