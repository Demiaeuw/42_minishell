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
static int  check_option_echo(char *str)
{
	int i;

	i = 0;
	while(str[i] != '-')
	{
		
		if (str[i] == '-')
		{
			i++;
			if (str[i] == 'n')
				break;
		}
		i++;
	}
// gestion si plusieurs 'n'
	while (str[i] == 'n')
		str[i]++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
/* ************************************************************************** */
int exe_echo(char *str)
{
	int option;
	int i;

	option = 0;
	i = 0;
	if(check_option_echo(str))
		option = 1;
	else 
		option = 0;

	while (str[i])
	{
		if (option == 0)
		{
			while (str[i] != "o")
				i++;
			i = i + 2;			
			printf("%s", &str[i]);
			printf("\n");
		}
		else if (option == 1)
		{
			while (str[i] != "n")
			{
				i++;
				while(str[i] == 'n')
					i++;
			}
			printf("%s", &str[i]);
		}	
		return (0);
	}

}