/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:09:51 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:45:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	leng(int c)
{
	int	s;

	if (c == 0)
		return (1);
	s = 0;
	if (c < 0)
		s = 1;
	while (c)
	{
		c = c / 10 ;
		s++;
	}
	return (s);
}

char	*ft_itoa(int c)
{
	char			*str;
	int				siz;
	unsigned int	num;

	siz = leng(c);
	str = (char *)malloc(sizeof(char) * (siz + 1));
	if (!str)
		return (NULL);
	str[siz] = '\0';
	siz-- ;
	str[siz] = '0';
	if (c < 0)
	{
		str[0] = '-';
		num = -c;
	}
	else
		num = c ;
	while (num)
	{
		str[siz] = ((num % 10) + '0');
		num = num / 10 ;
		siz-- ;
	}
	return (str);
}

// int main(void)
// {
//     int n;
// 	printf ("%d, Before Itoa :", n);
// 	ft_itoa (n);
// 	printf ("%d, Before Itoa :", n);
//     return 0;
// }