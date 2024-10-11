/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddfront.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:51:44 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 15:56:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void ft_lstadd_front(t_list **lst, t_list *new)
{
    if (new && lst)
    {
        new->next= *lst;
        *lst = new;
    }
}