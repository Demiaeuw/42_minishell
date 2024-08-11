/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_expanser_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:39:21 by yonieva           #+#    #+#             */
/*   Updated: 2024/08/11 15:39:21 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"\

char *resolve_path(const char *path) 
{
    char resolved_path[BUFFER_SIZE];
    char *p = resolved_path;
    char *end = resolved_path + sizeof(resolved_path) - 1;
    const char *s = path;

    if (!path || strlen(path) >= sizeof(resolved_path)) 
    {
        fprintf(stderr, "Path is too long or invalid.\n");
        return NULL;
    }

    while (*s) 
    {
        if (*s == '/' || *s == '\\') 
        {
            while (*s == '/' || *s == '\\') s++;
            if (!*s) break;
        }

        if (*s == '.') 
        {
            s++;
            if (*s == '/' || *s == '\\' || !*s) 
            {
                continue;
            } 
            else if (*s == '.' && (s[1] == '/' || s[1] == '\\' || !s[1])) {
                s += 2;
                if (p > resolved_path) 
                {
                    while (p > resolved_path && *(p - 1) != '/') {
                        p--;
                    }
                }
                continue;
            }
        }
        
        while (*s && *s != '/' && *s != '\\') 
        {
            if (p < end) 
            {
                *p++ = *s++;
            } 
            else 
            {
                fprintf(stderr, "Path is too long.\n");
                return NULL;
            }
        }
        
        if (p < end) 
        {
            *p++ = '/';
        }
    }
    
    if (p > resolved_path && *(p - 1) == '/') 
    {
        p--;
    }
    
    *p = '\0';
    
    char *result = strdup(resolved_path);
    if (!result) 
    {
        perror("strdup failed");
        return NULL;
    }
    
    return result;
}