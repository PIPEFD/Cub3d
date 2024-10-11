/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:33:52 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:45:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == 9 || str[i] == 10 || str[i] == 11 || str[i] == 12
		|| str[i] == 13 || str[i] == 32)
		i++ ;

	if (str[i] == '+' || str[i] == '-' )
	{
		if (str[i] == '-' )
			sign = -1 ;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' )
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

// int	main(void)
// {
// 	char	*nbr;

// 	nbr = "1234568";
// 	printf("%d\n", atoi(nbr));	
// 	printf("%d\n", ft_atoi(nbr));	
// 	return(0);
// }