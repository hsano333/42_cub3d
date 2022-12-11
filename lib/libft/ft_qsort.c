/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:08:35 by hsano             #+#    #+#             */
/*   Updated: 2022/11/29 18:52:31 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define LF "\n "

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	if (s1[i] == s2[i])
		return (0);
	else
		return (s1[i] - s2[i]);
}

static int	left_loop(char *tab[], char *pivot, int begin_ri, int li)
{
	while (li <= begin_ri)
	{
		if (ft_strcmp(&(tab[li][0]), &(pivot[0])) >= 0)
			break ;
		li++;
	}
	return (li);
}

static int	right_loop(char *tab[], char *pivot, int begin_li, int ri)
{
	while (ri >= begin_li)
	{
		if (ft_strcmp(&(tab[ri][0]), &(pivot[0])) <= 0)
			break ;
		ri--;
	}
	return (ri);
}

void	quick_sort(char *tab[], char *pivot, int li, int ri)
{
	int		begin_li;
	int		begin_ri;
	char	*tmp;

	begin_li = li;
	begin_ri = ri;
	while (1)
	{
		li = left_loop(tab, pivot, begin_ri, li);
		ri = right_loop(tab, pivot, begin_li, ri);
		if (li >= ri)
			break ;
		tmp = (tab[li]);
		tab[li] = tab[ri];
		tab[ri] = tmp;
		li++;
		ri--;
	}
	if (li - 1 > begin_li)
		quick_sort(tab, &(tab[(li - 1 + begin_li) / 2][0]), begin_li, li - 1);
	if (ri + 1 < begin_ri)
		quick_sort(tab, &(tab[(ri + 1 + begin_ri) / 2][0]), ri + 1, begin_ri);
}

void	ft_qsort(char **argv, size_t len)
{
	size_t	i;

	i = len;
	if (!argv || !argv[0])
		return ;
	if (i == 0)
	{
		while (argv[i])
			i++;
	}
	if (i > 0)
		quick_sort(argv, &(argv[i / 2][0]), 0, i - 1);
}
