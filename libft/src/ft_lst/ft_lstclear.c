/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:05:53 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:38:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *next_item;
    if (lst && *lst && del)
    {
        while(*lst)
        {
            next_item = (*lst) ->next;
            ft_lstdelone(*lst, del);
            *lst = next_item;
        }
        *lst = NULL;
    }
}