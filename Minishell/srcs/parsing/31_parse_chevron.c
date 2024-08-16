/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_parse_chevron.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:30:29 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/16 12:30:31 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	parse_chevrons_and_files(t_token *tokens) 
{
	t_token *current_token = tokens;

	while (current_token) 
	{
		char *value = current_token->value;
		char *ptr = value;

		while (*ptr) 
		{
			if (*ptr == '>') 
			{
				t_chevron_type type = OUT;
				ptr++;
				if (*ptr == '>') 
				{
					type = DOUBLE_OUT;
					ptr++;
				}
				while (*ptr == ' ') ptr++;
				char *file_start = ptr;
				while (*ptr && *ptr != ' ' && *ptr != '>' && *ptr != '<') ptr++;
				char *file_name = strndup(file_start, ptr - file_start);
				append_chevron(current_token, create_chevron(type, file_name));
				free(file_name);
			} 
			else if (*ptr == '<') 
			{
				t_chevron_type type = IN;
				ptr++;
				if (*ptr == '<') 
				{
					type = DOUBLE_IN;
					ptr++;
				}
				while (*ptr == ' ') ptr++;
				char *file_start = ptr;
				while (*ptr && *ptr != ' ' && *ptr != '>' && *ptr != '<') ptr++;
				char *file_name = strndup(file_start, ptr - file_start);
				append_chevron(current_token, create_chevron(type, file_name));
				free(file_name);
			} 
			else 
				ptr++;
		}
		current_token = current_token->next;
	}
	//print_chevron(tokens); 
}