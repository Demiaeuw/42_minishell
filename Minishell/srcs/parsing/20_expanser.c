/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_expanser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:19:26 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/24 11:19:26 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// EXPANSER

/*Commandes Simples

Description : Une seule commande sans arguments ni redirections.
Gestion : Exécutez la commande directement.

Commandes avec Arguments
Description : Une commande suivie d'un ou plusieurs arguments.
Gestion : Assemblez les arguments et exécutez la commande avec en 
parametre les arguments assembles et clean.

Pipes
Description : Plusieurs commandes reliées par des pipes (|), où la sortie d'une commande est l'entrée de la suivante.
Gestion : Configurez les descripteurs de fichiers pour rediriger les sorties et les entrées entre les commandes.

Redirections
Description : Commandes avec redirection d'entrée (<), de sortie (>), ou de sortie append (>>).
Gestion : Ouvrez les fichiers appropriés et redirigez les entrées/sorties.



Cas Complémentaires

Commandes avec Redirections et Pipes
Description : Une combinaison de pipes et de redirections dans une même commande.
Gestion : Assurez-vous de traiter les redirections avant de configurer les pipes, et ajustez les descripteurs de fichiers en conséquence.

Commandes en Contexte
Description : Commandes exécutées dans un contexte spécifique, par exemple, après une commande cd.
Gestion : Vérifiez et ajustez le contexte d'exécution si nécessaire.*/