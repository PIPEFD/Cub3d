/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:41:35 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:44:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0 ;
	while (str[i] != '\0' && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return ((char *) &str[i]);
	return (0);
}
// int main (void)
// {

// char str [] = "Hola Mundo" ;
// printf("Before strrchr str = %s \n", str);
// printf ("After strrchr str = %s \n", ft_strchr (str, 'a'));
// // printf ("FUNCTION : %s", strchr(str, 'a'));
// return (0);

// }