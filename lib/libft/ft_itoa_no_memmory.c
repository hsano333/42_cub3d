/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_no_memmory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:37:20 by hsano             #+#    #+#             */
/*   Updated: 2022/11/30 13:17:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>

static size_t	get_count(char *p, size_t n)
{
	size_t	a;
	size_t	i;	
	size_t	cnt;

	i = 0;
	cnt = 0;
	a = n;
	while (a)
	{
		p[i++] = (a % 10) + '0';
		a /= 10;
		cnt++;
	}
	return (cnt);
}

static int	zero_value(char *r, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		r[0] = '0';
		r[1] = '\0';
	}
	else
	{
		while (i < size)
		{
			r[i] = '0';
			i++;
		}
		r[i] = '\0';
	}
	return (true);
}

int	ft_itoa_no_memory(size_t n, size_t size, char *p, char *r)
{
	size_t	i;
	size_t	k;
	size_t	cnt;

	if (n == 0)
		return (zero_value(r, size));
	cnt = get_count(p, n);
	if (size > cnt)
		r[size - 1] = '\0';
	else
		r[cnt - 1] = '\0';
	if (size > 0 && cnt >= size)
		return (false);
	i = 0;
	while (size > 0 && i < size - cnt)
		r[i++] = '0';
	k = 0;
	while (k < cnt)
	{
		r[i + k] = p[cnt - k - 1];
		k++;
	}
	r[i + k] = '\0';
	return (cnt);
}
