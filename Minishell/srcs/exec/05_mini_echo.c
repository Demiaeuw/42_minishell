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
static int  check_option(char *av)
{
// Si le premier caractère n'est pas '-', 
// ou si le deuxième caractère n'est pas 'n', retourne 1.
    if (*av != '-' || *av++ != 'n')
        return (1);
    av++;
// gestion si plusieurs 'n'
    while (*av == 'n')
        av++;
    if (*av == '\0')
        return (0);
    return (1);
}
/* ************************************************************************** */
int exe_echo(char **av)
{
    int i;
//i = 1 = pas d option = saut de ligne, i = 0 = option '-n' = pas de saut
    i = 1;
// ignore premier argument (./minishell)
    av++;
//verif si option
    while (*av)
    {
        if(check_option(*av))
            break;
        i = 0;
        av++;
    }
// afficher les arguments restants
    while (*av)
    {
        printf("%s", *av);
        av++;
        if (*av)
            printf(" ");
    }
    if (i == 1)
        printf("\n");
        return (0);
}

// ------------------------------------------- Idée de echo ------------------------------------------ //
// void    echo(t_token *token)
// {
//     int test = 0;
//     t_token current_token = *token;

//     if (token->next->type == TOKEN_ARGUMENT && token ->next->value == "-n")
//     {
//         test = 1;
//         current_token = token->next;
//     }
//     if (token->next->type == TOKEN_STRING)
//     {
//         printf("%s", token->next->value);
//         if (test == 0)
//             printf("\n");
//     }
// }