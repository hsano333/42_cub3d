/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:30:58 by hsano             #+#    #+#             */
/*   Updated: 2022/11/18 21:48:49 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_split(char **split)
{
	size_t	j;

	j = 0;
	while (split[j])
		free(split[j++]);
	free(split);
	return (true);
}
