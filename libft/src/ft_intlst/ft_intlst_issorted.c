/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlst_issorted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:15:15 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 17:10:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"


int ft_intlst_issorted(t_intlst *lst)
{
    while (lst->next)
    {
        if(lst->value > lst->next->value)
                return (0);
        lst = lst->next;
        
    }
    return(1);
}