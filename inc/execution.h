/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:58:09 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/16 22:26:53 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h> 			//malloc + other functions
# include <stdio.h> 			//printf
# include "../libft/libft.h"

typedef struct s_env_nodes
{
	char				*str;
	//char	*var_name;
	char				first_letter;
	int					copied;
	struct s_env_nodes	*prev;
	struct s_env_nodes	*next;
}	t_env_nodes;

typedef struct s_export
{
	char			*str;
	//char			first_letter;
	int				smallest;
	struct s_export	*prev;
	struct s_export	*next;
}	t_export;

typedef struct s_struct_ptrs
{
	t_env_nodes	*env;
	//t_export	*export;
	t_env_nodes	*export;
}	t_struct_ptrs;

//**************
int	create_env(char **envp, t_struct_ptrs *data);
//int create_export(char **envp, t_struct_ptrs *data);
int create_export(t_struct_ptrs *data);		//new version?

//**************		BUILTINS
int		env(t_struct_ptrs *data);
int		pwd(t_struct_ptrs *data);

//**************		ERROR HANDLING
void	error_handling(t_struct_ptrs *data);
void	free_nodes(t_env_nodes **root);

#endif
