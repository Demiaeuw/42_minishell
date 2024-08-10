#include "../../include/minishell.h"

/**
 * Fonction pour exécuter la commande 'ls' en utilisant execve
 */
void	exe_ls(void)
{
	pid_t	pid;
	int		status;
	char	*argv[] = {"/bin/ls", NULL};
	char	*envp[] = {NULL};

	pid = fork();
	if (pid == 0)
	{
		// Processus enfant : exécute la commande ls
		if (execve("/bin/ls", argv, envp) == -1)
		{
			perror("Erreur execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		// Échec du fork
		perror("Erreur fork");
	}
	else
	{
		// Processus parent : attend la fin du processus enfant
		waitpid(pid, &status, 0);
	}
}
