/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:17:56 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:44:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dst = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (0);
	while (*(s1 + i))
	{
		*(dst + i) = *(s1 + i);
			i++;
	}
	while (*(s2 + j))
	{
			*(dst + i + j) = *(s2 + j);
			j++;
	}
	*(dst + i + j) = '\0';
	return (dst);
}

// int main (void)

// {
// 	char str1[] = "Hola Mundo";
// 	char str2[] = " Cruel";
// 	char  *str;
// 	str=ft_strjoin(str1, str2);

// 	printf("%s \n",str);
// 	return 0;	
// }