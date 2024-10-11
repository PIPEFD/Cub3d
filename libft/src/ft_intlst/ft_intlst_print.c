/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlst_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:35:48 by codespace         #+#    #+#             */
/*   Updated: 2023/10/16 17:09:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void ft_intlst_print(t_intlst *lst)
{

    t_intlst    *next_item;
    while(lst)
    {
        next_item=lst->next;
        ft_putnbr_fd((lst->value),1);
        ft_putchar_fd('\n', 1);
        lst = next_item;
    }
}