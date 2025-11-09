/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 23:03:56 by git               #+#    #+#             */
/*   Updated: 2025/11/08 23:03:56 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_get_num_length(int nb, int base_len)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb != 0)
	{
		nb /= base_len;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	int		i;
	long	n;
	int		len;
	char	*str;

	len = ft_get_num_length(nb, 10);
	i = len - 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (nb == 0)
		str[0] = '0';
	n = (long)nb;
	if (nb < 0)
		str[0] = '-';
	if (nb < 0)
		n *= -1;
	while (n != 0)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_htoa(int nb, int is_upper)
{
	int		i;
	long	n;
	char	*str;

	i = ft_get_num_length(nb, 16) - 1;
	str = malloc(sizeof(char) * (ft_get_num_length(nb, 16) + 1));
	if (!str)
		return (0);
	n = (long)nb;
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
		str[0] = '-';
	if (nb < 0)
		n *= -1;
	while (n != 0)
	{
		if (is_upper)
			str[i--] = "0123456789ABCDEF"[n % 16];
		else
			str[i--] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	str[ft_get_num_length(nb, 16)] = '\0';
	return (str);
}

int	ft_printf(const char *s, ...)
{
	(void)s;
	write(1, "Oh mais non", 10);
	return (10);
}

int	main(void)
{
	printf("%s\n", ft_itoa(-0));
	printf("%s\n", ft_itoa(299));
	printf("%s\n", ft_itoa(8393));
	printf("%s\n", ft_itoa(-22));
	printf("%s\n", ft_itoa(-372837));
	printf("%s\n", ft_htoa(0, 0));
	printf("%s\n", ft_htoa(222, 0));
	printf("%s\n", ft_htoa(892, 1));
	printf("%s\n", ft_htoa(-183, 1));
	printf("%s\n", ft_htoa(-27736, 1));
	return (0);
}
