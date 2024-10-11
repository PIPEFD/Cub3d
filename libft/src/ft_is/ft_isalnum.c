/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:46:08 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:39:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"


int	ft_isalnum(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else if (c >= 65 && c <= 90)
	{	
		return (1);
	}		
	else if (c >= 97 && c <= 122)
	{
		return (1);
	}
	else
		return (0);
}
//int main (void)
//{
//	printf("%d" ,ft_isalnum(65));
//}