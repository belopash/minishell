/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:21:03 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 20:09:27 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ENV_H
# define T_ENV_H

# include "libft.h"

typedef struct	s_env
{
	t_list	*list;
	char	*(*get)(struct s_env *, char *);
	void	(*add)(struct s_env *, char *);
	void	(*del)(struct s_env *, char *);
	void	(*destroy)(struct s_env *);
}				t_env;

t_env			*new_env(char **envs);

#endif
