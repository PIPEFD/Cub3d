/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:02:48 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 16:51:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"


int ft_check_format(char const *ptr, size_t len, va_list args)
{
    if(*ptr == 'c')
        len += ft_putchar_fd(va_arg(args,int), 1);
    else if (*ptr == '%')
        len += ft_putchar_fd(('%'), 1);
    else if (*ptr == 's')
        len += ft_putstr_fd(va_arg(args, char *), 1 );
    else if (*ptr == 'i' || *ptr == 'd')
        len += ft_putnbr_fd (va_arg(args, int), 1);
    else if (*ptr == 'u')
        len += ft_putnbr_unsigned(va_arg(args, unsigned int), 1);
    else if (*ptr == 'x' || *ptr == 'X' )
		len += ft_puthex(va_arg(args, unsigned int), ptr);
    else if (*ptr == 'p')
    {
        len += ft_putstr_fd (("0x"), 1);
        len += ft_puthex(va_arg(args, unsigned long int),ptr);
    }
    return (len);
}

int ft_printf(char const *str, ...)
{
    va_list	args;
	size_t	len;
	int		i ;
    
    va_start(args, str);
    len = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] != '%')
        {
            write(1,&str[i], 1);
            len++;
        }
        else if (str[i] == '%')
            if (str[i + 1])
                len = ft_check_format(&str[++i], len, args);
        i++;
    }
    return (va_end(args), (int)len);
}