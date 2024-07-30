/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_mini_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:23:21 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/22 12:23:21 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"     

/*check_option : Vérifie si un argument est une option '-n' valide.
  exe_echo : gère l'option -n pour ne pas ajouter de nouvelle ligne et affiche 
  les arguments avec des espaces entre eux. return 0 si ok.*/
/* ************************************************************************** */
static int  check_option_echo(char *str, int *start_index)
{
	int i;

	i = 0;
	if(str[i] != '-')
		return (0);
	i++;
	if (str[i] != 'n')
		return (0);
	// gestion si plusieurs 'n'
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0' || str[i] == ' ')
	{
		*start_index = i;
		return (1);
	}
	return (0);
}
/* ************************************************************************** */
int exe_echo(char *str, t_list *envp_list)
{
	int option;
	int i;
	int start_index;

	option = 0;
	i = 0;
	start_index = 0;
	while(str[i] == ' ')
		i++;
	i += 4;
	while(str[i] == ' ')
		i++;
	if (check_option_echo(&str[i], &start_index))
		option = 1;
	i = start_index;
	while(str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return(0);
	printf("%s", &str[i]);
	if (!option)
		printf("\n");
	return (0);
}