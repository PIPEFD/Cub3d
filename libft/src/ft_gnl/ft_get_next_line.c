/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:13:25 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 16:57:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif


char    *ft_back_line(char *line)
{
    size_t   i;
    char    *temp;

    i = 0;
    while (line[i] && line[i] != '\n')
        i++;
    if (line[i] == '\0')
        return (0);
    temp = ft_substr(line, i + 1, ft_strlen(line) - i);
    if (*temp == '\0')
    {
        free (temp);
        temp = NULL;
    }
    line[i + 1] = '\0';
    return (temp);
}

char    *function_read(int fd, char *buffer, char *temp)
{
    int     line_read;
    char    *temp_char;

    line_read = 1;
    while (line_read > 0)
    {
        line_read = read(fd, buffer, BUFFER_SIZE);
        if (line_read < 0)
            return (0);
        else if (line_read == 0)
            break;
        if (!temp)
        {
            temp = (char *) malloc (sizeof(char) * 1);
            temp[0] = '\0';
        }
        buffer[line_read] = '\0';
        temp_char = temp;
        temp = ft_strjoin(temp_char, buffer);
        free (temp_char);
        temp_char = NULL;
        if (ft_strchr(buffer, '\n'))
            break;
    }
    return (temp);
}

char *get_next_line(int fd)
{
    char        *line;
    char        *buffer;
    static char *temp;


    if (fd < 0 || BUFFER_SIZE <= 0)
        return(0);
    buffer = (char *) malloc(sizeof(char) + (BUFFER_SIZE + 1));
    if (!buffer)
            return(0);
    line = function_read(fd, buffer, temp);
    free (buffer);
    if (!line)
    {
        free (temp);
        temp = NULL;
        return (0);
    }
    temp = ft_back_line(line);
    return (line);
}