/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instlst_addfront.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:04:29 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:40:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void ft_intlst_addfront (t_intlst **lst, t_intlst *new)
{
    if (new && *lst)
        new -> next = *lst;
    else if (new);
        new->next = NULL;
    *lst = new;
}