/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 19:36:57 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/10 19:36:57 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	execute_execve(t_token *token, t_envfinal *env)
{
	pid_t	pid;
	int		status;

	char **str = convert_token(token);
	char **envp = convert_env(env);

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
		if (execve(str[0], args, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEEXITED(status))
			printf("L ENFANT DE SES MORTS %d\n", WIFEEXITED(status));
		else
			printf("L ENFANT N EST PAS NORMAL, IL EST BIZARRE\n");
	}
	free(str);
	free(envp);
}
