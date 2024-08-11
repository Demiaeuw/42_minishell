#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef enum s_token_type
{
    TOKEN_COMMAND,
    TOKEN_PIPE
}   t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    bool            is_builtin;
    char            *builtin_info;
    bool            is_last_command;
    struct s_token  *next;
}   t_token;

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
t_token *create_command_node(char *value);
void free_token_list(t_token *token_list);
void free_token_array(char **tokenarray);
size_t  ft_strlen(const char *c);
bool    is_builtin_command(char *com);
bool    check_builtin(char *value);
char    *get_builtin_info(char *value);
t_token *create_pipe_node(void);
void    add_token_node(t_token **head, t_token *new_node);
t_token *main_parsing(char *input);
char    **ft_split_quoted(const char *s);
void    print_token_list(t_token *head);


t_token *create_command_node(char *value)
{
    t_token *new_node;

    new_node = (t_token *)malloc(sizeof(t_token));
    if (!new_node)
        return (NULL);
    new_node->value = strdup(value);
    new_node->type = TOKEN_COMMAND;
    new_node->is_builtin = check_builtin(value);
    new_node->builtin_info = get_builtin_info(value);
    new_node->is_last_command = false;
    new_node->next = NULL;
    return (new_node);
}

bool    is_builtin_command(char *com)
{
    return (!strcmp(com, "cd") || !strcmp(com, "echo") || !strcmp(com, "pwd")
        || !strcmp(com, "env") || !strcmp(com, "export")
        || !strcmp(com, "unset") || !strcmp(com, "exit"));
}

bool    check_builtin(char *value)
{
    char *temp;
    int i = 0;
    int len = 0;

    while (value[len] && value[len] != ' ')
        len++;
    temp = malloc(sizeof(char) * (len + 1));
    if (!temp)
        return (false);
    while (i < len)
    {
        temp[i] = value[i];
        i++;
    }
    temp[i] = '\0';
    bool is_builtin = is_builtin_command(temp);
    free(temp);
    return (is_builtin);
}

char    *get_builtin_info(char *value)
{
    char *temp;
    int i = 0;
    int len = 0;

    while (value[len] && value[len] != ' ')
        len++;
    temp = malloc(sizeof(char) * (len + 1));
    if (!temp)
        return (NULL);
    while (i < len)
    {
        temp[i] = value[i];
        i++;
    }
    temp[i] = '\0';
    return (temp);
}

t_token *create_pipe_node(void)
{
    t_token *new_node;

    new_node = (t_token *)malloc(sizeof(t_token));
    if (!new_node)
        return (NULL);
    new_node->value = strdup("|");
    new_node->type = TOKEN_PIPE;
    new_node->is_builtin = false;
    new_node->builtin_info = NULL;
    new_node->is_last_command = false;
    new_node->next = NULL;
    return (new_node);
}

void    add_token_node(t_token **head, t_token *new_node)
{
    t_token *current;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

t_token *main_parsing(char *input)
{
    char    **tokenarray;
    t_token *token_list = NULL;
    t_token *new_node;
    t_token *pipe_node;
    int     i;

    tokenarray = ft_split_quoted(input);
    if (!tokenarray)
        return (NULL);

    i = 0;
    while (tokenarray[i])
    {
        new_node = create_command_node(tokenarray[i]);
        if (!new_node)
        {
            free_token_list(token_list);
            free_token_array(tokenarray);
            return (NULL);
        }
        add_token_node(&token_list, new_node);

        if (tokenarray[i + 1] != NULL)
        {
            pipe_node = create_pipe_node();
            if (!pipe_node)
            {
                free_token_list(token_list);
                free_token_array(tokenarray);
                return (NULL);
            }
            add_token_node(&token_list, pipe_node);
        }
        i++;
    }

    if (new_node != NULL)
        new_node->is_last_command = true;

    free_token_array(tokenarray);

    return (token_list);
}

void free_token_list(t_token *token_list)
{
    t_token *temp;

    while (token_list != NULL)
    {
        temp = token_list;
        token_list = token_list->next;

        if (temp->value)
            free(temp->value);

        if (temp->builtin_info)
            free(temp->builtin_info);

        free(temp);
    }
}

void free_token_array(char **tokenarray)
{
    int i = 0;

    if (!tokenarray)
        return;

    while (tokenarray[i] != NULL)
    {
        free(tokenarray[i]);
        i++;
    }

    free(tokenarray);
}

size_t  ft_strlen(const char *c)
{
    size_t  len;

    len = 0;
    while (c[len])
    {
        len++;
    }
    return (len);
}

char **ft_split_quoted(const char *str)
{
    char **result = NULL;
    int count = 0;
    bool in_quotes = false;
    char quote_char = '\0';

    result = malloc(sizeof(char *) * (strlen(str) / 2 + 2));
    if (!result)
        return NULL;

    for (int i = 0, start = 0; str[i]; i++)
    {
        if ((str[i] == '"' || str[i] == '\'') && (!in_quotes || quote_char == str[i]))
        {
            in_quotes = !in_quotes;
            quote_char = in_quotes ? str[i] : '\0';
        }

        if ((str[i] == '|' && !in_quotes) || str[i + 1] == '\0')
        {
            int len = i - start + (str[i + 1] == '\0');
            result[count] = strndup(str + start, len);
            if (!result[count])
            {
                free_token_array(result);
                return NULL;
            }
            count++;
            start = i + 1;
        }
    }

    result[count] = NULL;
    return result;
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size > 0)
	{
		while (--size && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}


void    print_token_list(t_token *head)
{
    t_token *current = head;

    while (current != NULL)
    {
        printf("Value: %s\n", current->value);
        printf("Type: %d\n", current->type);
        printf("Is Builtin: %s\n", current->is_builtin ? "Yes" : "No");
        if (current->is_builtin)
            printf("Builtin Info: %s\n", current->builtin_info);
        printf("Is Last Command: %s\n", current->is_last_command ? "Yes" : "No");
        printf("-----\n");
        current = current->next;
    }
}

int main(void)
{
    char test[] = "echo je test ma fonction | pour voir si ca marche";
    t_token *token = main_parsing(test);
    print_token_list(token);
    free_token_list(token);
    return 0;
}
