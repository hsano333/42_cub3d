/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:51:46 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 07:35:16 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	p[20];
	char	r[20];

	ft_itoa_no_memory(n, 0, &(p[0]), &(r[0]));
	ft_putstr_fd(r, fd);
}
//#include <stdlib.h>
//int main(int argc, char **argv)
//{
//	int c;
//	int	fd;
//	if (argc == 3)
//	{
//		c = atoi(argv[1]);
//		fd = atoi(argv[2]);
//		ft_putnbr_fd(c, fd);
//	}
//}
