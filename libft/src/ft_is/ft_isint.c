/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:28:05 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:39:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static void init_params(unsigned int *n, int *sign, unsigned int *digits)
{
    *n = 0;
    *sign = 1;
    *digits = 0;
}


int ft_isint(char *string)
{
    unsigned int n;
    int         sign;
    unsigned int digits;

    init_params(&n,&sign, &digits);
    if (*string == '+' || *string == '-')
    {
        if(*string++ == '-')
            sign = -1;
    }
    while(*string)
    {
        if (ft_isdigit(*string) && digits < 11 && n <= 214748364)
        {
                if( n == 214748364 && (*string == '9'||(*string == '8' && sign == 1)))
                    return (0);
                n = n * 10 + (*string++ - '0');
                digits++;
        }
        else
            return (0);
    }
    if (digits == 0)
        return(0);
    return (1);
}