/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:28:56 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:42:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (lst && *del)
    {
        del(lst -> content);
        free(lst);
    }
}