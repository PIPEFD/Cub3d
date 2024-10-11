/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:21:34 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 16:36:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t ft_puthex(unsigned long int num, char const *str)
{
    int len;

    len = 0;
    if (*str >= 32 || *str <= 122)
    {
        if (*str == 'x' || *str == 'p')
        {
            if (num >= 16)
                len += ft_puthex(num / 16, str);
            len += ft_putchar_fd (HEXX[num % 16], 1);
        }
    }
    if (*str == 'X')
    {
        if(num >= 16)
            len += ft_puthex(num / 16, str);
        len += ft_putchar_fd(HEX[num % 16], 1);
    }
    else
    {
        return (0);    
    }
    return (len);
}