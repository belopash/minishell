/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:56:33 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 14:52:04 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shell.h"
#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "t_builtin.h"
#include "builtins.h"

int	main(int argc, char **argv, char **envp)
{
	static t_builtin	builtins[] = {
		(t_builtin){"echo", ft_echo, 0, 0},
		(t_builtin){"cd", ft_cd, 0, 0},
		(t_builtin){"pwd", ft_pwd, 0, 0},
		(t_builtin){"env", ft_env, 0, 0},
		(t_builtin){"export", ft_export, 0, 0},
		(t_builtin){"unset", ft_unset, 0, 0},
		(t_builtin){"exit", ft_exit, 0, 0},
		{0, 0, 0, 0}};
	t_shell				*shell;

	(void)argc;
	(void)argv;
	if (!(shell = new_shell(envp, builtins)))
		return (1);
	shell->start(shell);
	shell->destroy(shell);
	return (0);
}
