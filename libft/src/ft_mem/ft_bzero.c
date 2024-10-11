/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:50:48 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:42:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_bzero(void *s, size_t n )
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i++] = 0;
	}
}

// int main (void)
// {
// 	char str [10] = "Hola Mundo" ;
// 	ft_bzero(str, 10);
// 	for(int x = 0; x < 10; x++)
// 		printf ("%c", str[x]);
// 	return(0);	
// }
