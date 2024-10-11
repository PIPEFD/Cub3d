/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:03:50 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:44:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = 0 ;
	ptr = 0;
	if (str[i] == (char)c)
		ptr = (char *) &str[i];
	while (str[i])
	{		
		i++;
		if (str[i] == (char)c)
			ptr = (char *) &str[i];
	}
	return (ptr);
}
// int main (void)
// {

// char str [] = "Hola Mundo" ;
// printf("Before strrchr str = %s \n", str);
// printf ("After strrchr str = %s \n", ft_strrchr (str, 'e'));
// /*printf ("FUNCTION : %s", strrchr(str, 'a'));	*/
// return (0);

// }