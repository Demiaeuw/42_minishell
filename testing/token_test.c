/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:15:33 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/24 16:00:50 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Structure de token
typedef struct s_token {
    char *value;
    struct s_token *next;
} t_token;

// Fonction pour créer un nouveau token
t_token *new_token(char *value) {
    t_token *token = malloc(sizeof(t_token));
    token->value = strdup(value);
    token->next = NULL;
    return token;
}

// Fonction de tokenization de base
t_token *tokenize(char *input) {
    t_token *head = NULL;
    t_token *current = NULL;
    char *token = strtok(input, " ");

    while (token != NULL) {
        t_token *new = new_token(token);
        if (head == NULL) {
            head = new;
            current = head;
        } else {
            current->next = new;
            current = current->next;
        }
        token = strtok(NULL, " ");
    }
    return head;
}

// Fonction pour afficher les tokens
void    print_tokens(t_token *tokens)
{
    while (tokens != NULL)
    {
        printf("TOKEN_TYPE : %s\n", token->)
        printf("Token value : %s\n", tokens->value);
        tokens = tokens->next;
    }
}

int main(int ac, char **av) {
    (void)ac;
    char input = av[1];
    t_token *tokens = tokenize(input);
    print_tokens(tokens);
    return 0;
}
