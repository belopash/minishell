#include "t_shell.h"
#include <stdlib.h>
#include "libft.h"
#include "utils.h"

int main(int argc, char **argv, char **envp)
{
	t_shell *shell;

	if (!(shell = newShell(envp)))
		return (-1);
	shell->start(shell);
	return (0);
}
