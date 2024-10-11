/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:43:45 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 16:01:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
    t_list  *first_item;
    t_list  *temp;
    
    if(f == NULL || lst == NULL)
        return (NULL);
    while(lst)
    {
        temp = ft_lstnew(f(lst -> content));
        if (lst == NULL)
        {
            ft_lstclear(&first_item, del);
            return (NULL);
        }
    ft_lstadd_back(&first_item,temp);
    lst = lst->next;  
    }
    return (first_item);
}