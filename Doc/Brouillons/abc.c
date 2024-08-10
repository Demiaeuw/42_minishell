char	**convert_token(t_token *token)
{
	t_token	*current;
	char	**str;
}

void	execute_execve(t_token *token, t_envfinal *env)
{
	pid_t	pid;
	int		status;

	char **str = //fonction pour convertir le token en tab de tab.
	char **envp = //fonction pour convertir la liste de l env en tab de tab.

	if (!str || !envp)
	{
		perror("Memory allocation failed");
		free(str);
		free(envp);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(str);
		free(envp);
		return ;
	}
	else if (pid == 0)
	{
		printf("huehuehuehue");
	}
}