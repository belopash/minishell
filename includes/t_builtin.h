/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_builtin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:18:01 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/21 19:51:40 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_BUILTIN_H
# define T_BUILTIN_H

# include "./libft.h"

typedef struct s_shell	t_shell;

typedef struct	s_builtin
{
	char		*name;
	int			(*command)(struct s_builtin *, char **);
	void		(*destroy)(struct s_builtin *);
	t_shell		*shell;
}				t_builtin;

typedef struct	s_builtins_manager
{
	t_list		*list;
	t_builtin	*(*get)(struct s_builtins_manager *, char *);
	void		(*destroy)(struct s_builtins_manager *);
	t_shell		*shell;
}				t_builtins;

t_builtin		*new_builtin(t_shell *shell, char *name,
							int (*command)(t_builtin *builtin, char **argv));
t_builtins		*new_builtins(t_shell *shell, t_builtin *builtins);

#endif
