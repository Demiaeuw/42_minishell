/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:53:07 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/19 18:15:44 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Main de gestion des arguments
 * 1/ join
 * 2/ split comme il faut
 * 3/ créer les tokens par type au fur et a meusure des arguments en liste chainé
 * 4/ free le tab de char
 * 5/ retourne la liste chainé de tokken
 */
char	*main_argument(int ac, char **av)
{
	char	*joined_args;

	joined_args = step01(ac, av);
	if (!joined_args)
		return (NULL);
	return (joined_args);
}



/**
 *  Fonction pour joindre tous les arguments en une seule chaîne
 */ 
char	*step01(int ac, char **av)
{
	int		total_length;
	char	*joined_args;
	int		i;
	int		quote_open;
	int		double_quote_open;

	total_length = 0;
	quote_open = 0;
	double_quote_open = 0;
	i = 1;
	while (i < ac)
		total_length += ft_strlen(av[i++]) + 1;
	joined_args = (char *)safe_malloc(total_length * sizeof(char));
	i = 1;
	ft_strcpy(joined_args, av[i++]);
	while (i < ac)
	{
		ft_strcat(joined_args, " ");
		ft_strcat(joined_args, av[i++]);
	}
	// Check for unclosed quotes and close them
	i = 0;
	while (joined_args[i])
	{
		if (joined_args[i] == '\'' && double_quote_open == 0)
			quote_open = !quote_open;
		else if (joined_args[i] == '"' && quote_open == 0)
			double_quote_open = !double_quote_open;
		i++;
	}
	if (quote_open)
		ft_strcat(joined_args, "'");
	if (double_quote_open)
		ft_strcat(joined_args, "\"");

	// Afficher le résultat avant de retourner
	printf("Joined arguments: %s\n", joined_args);

	return (joined_args);
}


/**
 * Fonction pour créer le tableau de tableau de char en fonction des guillemet
 */
// char	**step02(char *str)
// {
	
// }
/**
 * Fonction pour afficher le tableau de char
 */
void	print_split_args(char **array)
{
	int	i;

	if (array == NULL)
	{
		printf("Aucun argument à afficher.\n");
		return ;
	}
	i = 0;
	while (array[i])
	{
		printf("Argument %d: %s\n", i, array[i]);
		i++;
	}
}

/**
 * creation de tokken + ajout du type en fonction de ce qu'il y a ecrit et retourne la liste chainé
 */ 
// void	step03()
// {
	
// }
