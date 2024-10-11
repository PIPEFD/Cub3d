/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlst_maxval.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:18:38 by codespace         #+#    #+#             */
/*   Updated: 2023/11/07 19:09:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/libft.h"

int ft_intlst_maxval(t_intlst *lst)
{
    int    max;

    if (lst)
    {
        max = -2147483648;
        while(lst)
        {
            if (lst->value > max)
                max =lst->value;
            lst = lst->next;
        }
        return (max);
    }
    return (0);
}