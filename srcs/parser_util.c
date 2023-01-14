/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:45:31 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/14 23:18:12 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

bool	ft_atoi_custom(long long *result, const char *str)
{
	long long	tmp;
	long long	minus;

	tmp = 0;
	minus = 1;
	while (ft_strchr(" \t\n\v\f\r", *str))
		str++;
	if (ft_strchr("+-", *str))
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (false);
	while (ft_isdigit(*str))
	{
		tmp *= 10;
		tmp += *str - '0';
		if (tmp < INT_MIN || INT_MAX < tmp)
			return (false);
		str++;
	}
	*result = (int)tmp * minus;
	return (true);
}
