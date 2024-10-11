/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:57:26 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:43:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s1 ;
	unsigned char	*s2 ;

	i = 0;
	s1 = (unsigned char *) dst;
	s2 = (unsigned char *) src;
	if (s1 == 0 && s2 == 0)
		return (NULL);
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dst);
}

// int main (void)
// {
// const char src[50] = "Hola Mundo!!";
//    char dest[50] = "Heloooo!!";
//    printf ("%s", ft_memcpy(dest, src, 12));
// return(0);
// }