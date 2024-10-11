/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 06:35:41 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:42:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void ft_lstiter(t_list *lst, void (*f)(void *))
{
    if (f)
    {
        while (lst)
        {
            f(lst->content);
            lst = lst->next;
        }
        
    }   
}