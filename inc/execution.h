/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:58:09 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/21 14:20:14 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include <stdlib.h> //malloc + other functions
#include <stdio.h>	//printf
#include <unistd.h> //getcwd
#include "../libft/libft.h"

#define FAIL 1
#define SUCCESS 0

typedef struct s_list_base
{
	struct s_list_base *next;
	struct s_list_base *prev;
} t_list_base;

typedef struct s_env_nodes
{
	t_list_base base;
	char *var_name;
	char *var_value;
	int copied;
	// struct s_env_nodes	*prev;
	// struct s_env_nodes	*next;
} t_env_nodes;

typedef enum
{
	CMD,
	ARG,
} t_tokens;

typedef struct s_inp
{
	t_list_base	base;
	t_tokens	token_type;
	char		**token_value;
} t_inp;


typedef struct s_struct_ptrs
{
	t_env_nodes *env;
	t_env_nodes *export;
	//char **cmd_arr;
	t_inp		*inp;
} t_struct_ptrs;

//**************		ENV & EXPORT
int create_env(char **envp, t_struct_ptrs *data);
// int create_export(char **envp, t_struct_ptrs *data);
int create_export(t_struct_ptrs *data); // new version?

//**************		BUILTINS
int env(t_struct_ptrs *data);
int pwd(t_struct_ptrs *data);
int export(t_struct_ptrs *data);
int unset(t_struct_ptrs *data);

//**************		NODE UTILS
int			append_node(t_list_base *list_to_modify, t_list_base *new_var);
t_list_base *find_last(t_list_base *root);

//**************		STRING UTILS
int 	ft_strcmp(char *s1, char *s2);
char	*ft_strndup(const char *s, size_t len);

//**************		ERROR HANDLING
void error_handling(t_struct_ptrs *data);
void free_env_nodes(t_env_nodes **root);

//*************			DEBUGGING __ DELETEEEEEEEE!!!!!!!!!!!!!!!!!
void    print_list(t_list_base *head, void (*print_node)(void *));
void    print_env_nodes(void *node);
void    print_inp_nodes(void *node);

#endif
