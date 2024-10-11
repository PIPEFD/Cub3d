/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlst_addback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 09:44:46 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 17:02:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void ft_intlst_addback(t_intlst **lst, t_intlst * new)
{
    t_intlst    *tmp;
    
    if (new && *lst)
    {
        if(*lst == NULL)
           *lst = new;
        else
        {
            tmp = ft_intlst_last(*lst);
            tmp->next = new;
        }
    }
   
}