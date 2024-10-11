/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:31:25 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:44:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	count;

	count = 0;
	while (*s != '\0')
	{
		count++ ;
		s++;
	}
	return (count);
}

// int main (void)
// {
//  char str [10]= "hola mundo" ;
//  printf ("%lu \n", ft_strlen(str));
//  printf ("%lu", strlen(str));
// }