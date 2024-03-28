/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freejoin_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:28:42 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/26 11:23:22 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_freejoin_char(const char *s, char c)
{
	size_t	len_s;
	char	*result;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	result = (char *)malloc(len_s + 1 + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s, len_s + 1);
	result[len_s] = c;
	result[len_s + 1] = '\0';
	free((char *)s);
	return (result);
}
