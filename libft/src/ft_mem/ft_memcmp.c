/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:07:08 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/16 16:10:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*b1;
	unsigned char	*b2;
	size_t			i;

	if (n == 0)
		return (0);
	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	i = 0;
	while ((i < n - 1) && (*(b1 + i) == *(b2 + i)))
		i++;
	return (*(b1 + i) - *(b2 + i));
}

// int main (void)
// {
//  int ret ;
//  int res ;

//     //If s1 and s2 equal
//     ret = ft_memcmp("hola","hola",3);
//     res = memcmp("hola","hola",3);

//     printf("ret = %d\n",ret);
// 	printf("res = %d\n \n",res);
//     //if first char of s1 is large to s2
//     ret = ft_memcmp("ola","oola",3);
// 	res = memcmp("ola","oola",3);
//     printf("ret = %d\n",ret);
// 	printf("res = %d\n \n",res);

//     //if first char of s1 is small to s2
//     ret = ft_memcmp("holaA","hola",5);
//     res = memcmp("holaA","hola",5);
// 	printf("ret = %d\n",ret);
// 	printf("res = %d\n \n",res);

//     return 0;
// }