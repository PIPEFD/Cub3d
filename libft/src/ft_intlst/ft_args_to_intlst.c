/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_to_intlst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 07:01:21 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 17:02:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/libft.h"

t_intlst  *ft_args_to_intlst(int argc, char **argv)
{
    int         i;
    t_intlst    *a;
    t_intlst    *tmp;

    i = 1;
    while (i < argc)
    {
        if ( i == 1)
            a = ft_intlst_new(ft_atoi((*(argv + i))));
        else
        {

            tmp = ft_intlst_new(ft_atoi((*(argv + i))));
            ft_intlst_addback(&a, tmp);
        }  
        i++;
    }
    return (a);   
}