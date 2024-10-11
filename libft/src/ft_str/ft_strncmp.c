/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:09:31 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:44:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_strncmp( const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*z1;
	unsigned char	*z2;

	z1 = (unsigned char *)s1;
	z2 = (unsigned char *)s2;
	i = 0;
	while (z1[i] != '\0' && z2[i] != '\0' && i < n)
	{
		if (z1[i] != z2[i])
			return (z1[i] - z2[i]);
		i++;
	}
	if (i < n)
	{
		return (z1[i] - z2[i]);
	}
	return (0);
}

// int	main(void)
// {
// 	char	str1[] = " Hola Mundo";
// 	char	str2[] = " Hola undo";
// 	printf("Before strncmp str1 = %s \n 		str2 = %s \n", str1, str2);
// 	printf ("After strncmp str = %d \n", ft_strncmp (str1, str2, 25 ));
// 	printf("Original function  = %d \n", strncmp(str1, str2, 25));
// }