/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:55:16 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 16:16:00 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_history	*init_history(void)
{
	t_history	*history;

	history = (t_history *)malloc(sizeof(t_history));
	if (!history)
		return (NULL);
	history->cmd = NULL;
	history->next = NULL;
	history->prev = NULL;
	return (history);
}

void	save_history(t_history **history, char *cmd)
{
	t_history	*new_node;
	t_history	*current;

	new_node = (t_history *)malloc(sizeof(t_history));
	if (!new_node)
		return ;
	new_node->cmd = ft_strdup(cmd); // Remplace `ft_strdup` par une fonction d'allocation mémoire et de copie
	new_node->next = NULL;

	if (*history == NULL || (*history)->cmd == NULL)
	{
		free(*history);
		*history = new_node;
		new_node->prev = NULL;
	}
	else
	{
		current = *history;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
}

void	select_history(t_history *history)
{
	t_history	*current;
	char		c;
	struct termios oldt, newt;

	// Obtenir les paramètres actuels du terminal
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO); // Désactiver le mode canonique et l'écho
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	current = history;
	while (current && current->next != NULL)
		current = current->next;

	while (1)
	{
		c = getchar();
		if (c == 27) // Séquence d'échappement
		{
			getchar(); // Ignorer le caractère '['
			c = getchar();
			if (c == 'A') // Flèche du haut
			{
				if (current)
				{
					printf("\33[2K\rMinishell 🌟> %s", current->cmd); // Effacer la ligne actuelle et afficher l'historique
					current = current->prev;
				}
			}
		}
		if (c == '\n') // Entrée pour quitter
			break;
	}

	// Restaurer les paramètres du terminal
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void	free_history(t_history *history)
{
	t_history	*current;
	t_history	*next;

	current = history;
	while (current)
	{
		next = current->next;
		free(current->cmd);  // Libère la mémoire pour la commande
		free(current);       // Libère le nœud de l'historique
		current = next;
	}
}

