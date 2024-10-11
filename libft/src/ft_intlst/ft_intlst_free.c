/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlst_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:19:15 by codespace         #+#    #+#             */
/*   Updated: 2023/10/19 16:23:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"


void ft_intlst_free(t_intlst **lst)
{
    t_intlst *tmp;
    while(*lst)
    {
        tmp = *lst;
        *lst = (*lst)->next;
        free(tmp);
    }
}