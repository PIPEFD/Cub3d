/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:48:08 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:44:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f (i, &s[i]);
		i++;
	}
}

void	myfunc(unsigned int i, char *string)
{
	*string = *string + i;
}
// int main(void)
// {
// 	char str[] = "hola";
// 	printf ("string sin modificar; %s \n", str);
// 	ft_striteri(str, myfunc);
// 	printf ("string modificado; %s \n", str);
// 	return 0 ;
// }