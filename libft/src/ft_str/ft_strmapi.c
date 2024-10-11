/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:42:44 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:44:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s)
		return (0);
	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s)) + 1);
	if (!str)
		return (0);
	while (s[i])
	{
		str[i] = f (i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}	

char	my_func(unsigned int i, char str)
{
	if (i % 2 == 0)
		return (str - 32);
	else
		return (str);
}

// int main (void)
// {
// 	char *str;
// 	char *res ;
// 	str = "!Hola Mundo¡" ;
// 	printf("Before strmapi src = %s\n", res);
// 	res = ft_strmapi(str, my_func);
// 	printf("After strmapi src = %s\n", res);
// 	return (0);

// }
