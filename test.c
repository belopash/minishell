#include "t_shell.h"

int main(int argc, char **argv, char **env)
{
	t_shell *shell;

	if (!(shell = newShell(env)))
		return (-1);
	shell->start(shell);
	return (0);
}
