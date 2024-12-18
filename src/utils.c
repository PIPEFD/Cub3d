/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:07:57 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/31 16:39:17 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mod_strcomp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (1);
	return (0);
}

char	*mod_join(char *s1, char *s2)
{
	char	*str;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, size);
	ft_strlcat(str, s2, size);
	free(s1);
	return (str);
}

char	*ft_read_the_file(char *file_name)
{
	int		fd;
	int		bytes;
	char	*line;
	char	buff[2];

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buff[1] = '\0';
	line = ft_strdup("");
	while (1)
	{
		bytes = read(fd, buff, 1);
		if (bytes == -1)
			return (close(fd), free(line), NULL);
		if (bytes == 0)
			return (close(fd), line);
		line = mod_join(line, buff);
	}
}

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}
