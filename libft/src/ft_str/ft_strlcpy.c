/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:43:28 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:44:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*pt_src;

	pt_src = (char *)src;
	i = 0;
	if (size > 0)
	{
		while (pt_src[i] != '\0' && i < size - 1)
		{
			dst[i] = pt_src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

// int	main(void)
// {
// 	char src[] = "WORLD.";
// 	char dst[] = "HELLO.";
// 	printf("BEFORE\n\tsrc: %s\n\tdes: %s\n", src, dst);
// 	ft_strlcpy(dst, src, 3);
// 	printf("AFTER\n\tsrc: %s\n\tdes: %s\n", src, dst);
// 	return (0);
// }