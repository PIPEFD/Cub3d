/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:55:28 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:43:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"


void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *) dst;
	s2 = (unsigned char *) src;
	if (s1 == 0 && s2 == 0)
		return (NULL);
	if ((s2 - s1) < 0)
	{
		while (len > 0)
		{
			s1[len - 1] = s2[len - 1];
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*s1++ = *s2++;
			len--;
		}
	}
	return (dst);
}

// int main (void)
// {
// char dest[] = "loqjsjs";
//char *src;

//src = dest ;
//   const char src[]  = "hoola";

//    printf("Before memmove dest = %s, src = %s\n", dest, src);
//    ft_memmove(dest, src , 5);
//    printf("After memmove dest = %s, src = %s\n", dest, src);

//    return(0);
// }
