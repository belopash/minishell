#include "t_shell.h"
#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "t_builtin.h"
#include "builtins.h"

int main(int argc, char **argv, char **envp)
{
	static t_builtin builtins[] = {
		(t_builtin){"echo", ft_echo},
		(t_builtin){"cd", ft_cd},
		(t_builtin){"pwd", ft_pwd},
		(t_builtin){"env", ft_env},
		(t_builtin){"export", ft_export},
		(t_builtin){"unset", ft_unset},
		{0, 0}};
	t_shell *shell;

	if (!(shell = new_shell(envp, builtins)))
		return (-1);
	shell->start(shell);
	shell->destroy(shell);
	return (0);
}
