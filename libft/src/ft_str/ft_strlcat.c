/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:15:17 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/16 16:36:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)

{
	unsigned int	d;
	unsigned int	s;
	unsigned int	i;

	d = 0 ;
	s = 0 ;
	i = 0 ;
	while (dst[d])
		d++;
	while (src[s])
		s++;
	if (size <= d)
		return (s + size);
	while (src[i] && (d + i) < (size -1))
	{
			dst[d + i] = src[i];
		i++;
	}
	dst[d + i] = '\0';
	return (s + d);
}

// int	main(void)
// {
// 	char src[] = "CRUEL.";
// 	char dst[] = "HELLO WORLD";
// 	unsigned int n;

// 	n = 8;

// 	printf("BEFORE\n\tsrc: %s\n\tdes: %s\n", src, dst);
// 	ft_strlcat(dst, src, n);

// 	printf("AFTER\n\tsrc: %s\n\tdes: %s\n", src, dst);
// 	return (0);
// }
