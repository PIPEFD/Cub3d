/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlst_isresorted.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:24:14 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:40:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"


int ft_intlst_isresorted(t_intlst *lst)
{
    while(lst->next)
    {
        if(lst->value > lst ->next->value)
            return(0);
            lst = lst->next;
    }
    return (1);
}