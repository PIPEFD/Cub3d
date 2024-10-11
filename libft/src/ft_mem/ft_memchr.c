/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:34:48 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:42:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	chr;
	unsigned char	*result;

	i = 0;
	chr = (unsigned char)c;
	result = (unsigned char *)s;
	while (i < n)
	{
		if (result[i] == chr)
			return (&result[i]);
		i++;
	}
	result = NULL;
	return (result);
}

// int main () {
//    const char str[] = "Hola Mundo";
//    const char ch = 'h';
//    char *ret;

//    ret = ft_memchr(str, ch, ft_strlen(str));
//    	printf ("found at position %s.\n",memchr(str ,ch, 5));

//    	if (ret != NULL)
//     {
// 	}
// 	else
// 	 {
//         printf (" search character '%c' not found\n", ch);
//     }
//    return(0);
// }