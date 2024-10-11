/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:18:06 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:44:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s1_new;
	int		size;

	size = ft_strlen(s1);
	s1_new = malloc (sizeof(char) * size + 1);
	if (!s1_new)
		return (NULL);
	i = 0 ;
	while (s1[i] != '\0')
	{
	s1_new[i] = s1[i];
		i++;
	}
	s1_new[i] = s1[i];
	return (s1_new);
}

// int main(void)
// {
//  printf ("%s \n", ft_strdup("Hola Mundo!"));
//  return (0);
// }