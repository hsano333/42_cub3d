/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:23:11 by hsano             #+#    #+#             */
/*   Updated: 2022/11/29 22:03:04 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

int	ft_putstr_fd_r(char *s, int fd)
{
	size_t	len;

	if (!s)
		return (true);
	len = ft_strlen(s);
	write(fd, s, len);
	return (true);
}
//#include <stdlib.h>
//int main(int argc, char **argv)
//{
//	char *c;
//	int	fd;
//	if (argc == 3)
//	{
//		c = argv[1];
//		fd = atoi(argv[2]);
//		ft_putstr_fd(c, fd);
//	}
//}
