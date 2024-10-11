/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:15:52 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 16:33:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t ft_putnbr_unsigned(unsigned int n, int fd)
{
    int len;

    len = 0;
    if (n > 9)
        len += ft_putnbr_unsigned(n / 10, fd);
    len += ft_putchar_fd((n % 10) + 48, fd);
    return (len);    
}