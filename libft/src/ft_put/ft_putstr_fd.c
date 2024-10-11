/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:23:46 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:43:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	while (s + i && s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	return (i);
}
