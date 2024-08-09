/*int	to_home(char *commande)
{
	char	*current_dir;
	int		is_home;

	if (commande == NULL || commande[0] == '\0')
		return (1);
	current_dir = getcwd(0, 0);
	if (commande != NULL && current_dir == NULL)
		is_home = 1;
	else
		is_home = 0;
	free(current_dir);
	return(is_home);
}*/
/*
int	mini_cd(char *str, t_envfinal *env)
{
	char	*to_dir;
	char	*new_dir;
	char	*prev_dir;

	if (arg == NULL || arg[0] == '\0')
	{
		to_dir = find_env_variable(env, "HOME");
		if (!to_dir)
		{
			printf("je vais aller mettre le masque\n");
			return (1);
		}
	}
	else
		to_dir = str;
	prev_dir = getcwd(0, 0);
	if (prev_dir == NULL)
	{
		perror("cd");
		return(1);
	}
	if (chdir(to_dir) != 0)
	{
		printf(("No such file or directory\n"), to_dir);
		free(prev_dir);
		return (1);
	}
	new_dir = getcwd(0, 0);
	if (new_dir == NULL);
	{
		perror("cd");
		free(prev_dir);
		return (1);
	}
	update_env_variable(env, "PWD", home_env->content);
	update_env_variable(env, "OLDPWD", home_env->content);
	free(prev_dir);
	free(new_dir);
	return(0);
}*/
/*int		cd_comp(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else
		return (0);
}*/