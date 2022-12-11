/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 20:03:06 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 07:36:01 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa(long n, char *r)
{
	char	p[30];

	ft_itoa_no_memory(n, 0, p, &(r[0]));
	return (r);
}
//#include <stdlib.h>
//int main(int argc, char **argv)
//{
//	char tmp[100];
//	long c;
//	int	fd;
//	if (argc == 2)
//	{
//		c = atol(argv[1]);
//		ft_ltoa(c, tmp);
//		printf("c=%ld, result=%s\n", c, tmp);
//		//fd = atoi(argv[2]);
//		//ft_putnbr_fd(c, fd);
//	}
//}
