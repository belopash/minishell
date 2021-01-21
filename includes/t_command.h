/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/21 19:32:19 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COMMAND_H
# define T_COMMAND_H

# include "./libft.h"
# include "./t_shell.h"

# define DEFAULT 0
# define PIPE 01
# define REDIRECT 010
# define REDPIPE 011

typedef struct	s_flags
{
	int	redir_r;
	int	redir_l;
}				t_flags;

typedef struct	s_command
{
	int		input;
	int		output;
	t_list	*list;
	int		type;
	char	*filename;
	t_flags	flags;
	t_shell	*shell;
	int		(*execute)(struct s_command *);
	void	(*destroy)(struct s_command *);
}				t_command;

t_command		*new_command(t_shell *shell, int input, int output);
int				execute(t_command *command);

#endif
