/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:08:08 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 16:00:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *temp;
    if (new && lst)
    {
        if (*lst == NULL)
            *lst = new;
        else
        {
            temp = ft_lstlast(*lst);
            temp->next=new;
        }
    }
}