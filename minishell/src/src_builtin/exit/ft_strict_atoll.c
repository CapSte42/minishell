/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strict_atoll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:34:35 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	set_and_return(int *nptr, int value)
{
	*nptr = value;
	return (0);
}

static int	get_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

static long long	parse_num(const char *nptr, int *error, size_t i, int sign)
{
	long long	num;
	int			digit;

	num = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t')
		i++;
	if (nptr[i] == '\0')
		return (set_and_return(error, 1));
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = get_sign(nptr[i]);
		i++;
	}
	if (nptr[i] < '0' || nptr[i] > '9')
		return (set_and_return(error, 2));
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		digit = nptr[i] - '0';
		if (num > (LLONG_MAX - digit) / 10)
			return (set_and_return(error, 3));
		num = num * 10 + digit;
		i++;
	}
	return (num * sign);
}

long long	ft_atoll(const char *nptr)
{
	long long	num;
	int			error;

	error = 0;
	num = parse_num(nptr, &error, 0, 1);
	if (error != 0)
		return (0);
	return (num);
}
