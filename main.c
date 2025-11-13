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

#include "../libft/libft.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int	ft_get_num_length(int nb, int base_len)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= base_len;
		len++;
	}
	return (len);
}

int	ft_get_str_len(int nb, int num_len, int full_len, int show_sign)
{
	int	str_len;

	str_len = num_len;
	if (full_len != -1 && full_len > num_len)
		str_len = full_len;
	if (nb < 0 || show_sign)
		str_len++;
	return (str_len);
}

char	*ft_get_padded_string(int nb, int num_len, int full_len, int show_sign)
{
	int		i;
	char	*str;
	int		str_len;

	str_len = ft_get_str_len(nb, num_len, full_len, show_sign);
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (nb < 0)
		*str = '-';
	else if (show_sign)
		*str = '+';
	if (nb < 0 || show_sign)
		str++;
	while (full_len != -1 && i < full_len - num_len)
		str[i++] = '0';
	if (nb < 0 || show_sign)
		str--;
	if (nb == 0)
		str[str_len - 1] = '0';
	str[str_len] = '\0';
	return (str);
}

char	*ft_itoa_pad(int nb, int full_len, int show_sign)
{
	int		i;
	long	n;
	int		num_len;
	char	*str;

	num_len = ft_get_num_length(nb, 10);
	str = ft_get_padded_string(nb, num_len, full_len, show_sign);
	if (str == NULL)
		return (NULL);
	if (nb == 0)
		return (str);
	n = (long)nb;
	if (nb < 0)
		n *= -1;
	i = ft_get_str_len(nb, num_len, full_len, show_sign);
	while (n != 0)
	{
		str[--i] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_htoa_pad(int nb, int is_upper, int full_len)
{
	int		i;
	long	n;
	int		num_len;
	char	*str;

	num_len = ft_get_num_length(nb, 16);
	str = ft_get_padded_string(nb, num_len, full_len, 0);
	if (str == NULL)
		return (NULL);
	if (nb == 0)
		return (str);
	n = (long)nb;
	if (nb < 0)
		n *= -1;
	i = ft_get_str_len(nb, num_len, full_len, 0);
	while (n != 0)
	{
		if (is_upper)
			str[--i] = "0123456789ABCDEF"[n % 16];
		else
			str[--i] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (*s++)
		counter++;
	return (counter);
}

void	ft_putstr_truncate(const char *s, int full_len)
{
	size_t	len;

	len = ft_strlen(s);
	if (full_len < (int)len)
		write(1, s, full_len);
	else
		write(1, s, len);
}

int	main(void)
{
	printf("|---| INT |---|\n\n");
	printf("%s\n", ft_itoa_pad(-0, -1, 1));
	printf("%+d\n\n", -0);
	printf("%s\n", ft_itoa_pad(299, 44, 1));
	printf("%+.44d\n\n", 299);
	printf("%s\n", ft_itoa_pad(8393, 3, 0));
	printf("%.3d\n\n", 8393);
	printf("%s\n", ft_itoa_pad(-22, 100, 1));
	printf("%+.100d\n\n", -22);
	printf("%s\n", ft_itoa_pad(-372837, -1, 1));
	printf("%+d\n", -372837);
	printf("\n\n|---| HEX |---|\n\n");
	printf("%s\n", ft_htoa_pad(0, 0, -1));
	printf("%x\n\n", 0);
	printf("%s\n", ft_htoa_pad(222, 0, -1));
	printf("%x\n\n", 222);
	printf("%s\n", ft_htoa_pad(892, 1, -1));
	printf("%X\n\n", 892);
	printf("%s\n", ft_htoa_pad(183, 1, -1));
	printf("%X\n\n", 183);
	printf("%s\n", ft_htoa_pad(27736, 1, -1));
	printf("%X\n", 27736);
	printf("\n\n|---| STRING |---|\n");
	ft_putstr_truncate("oh mais non!", 5);
	printf("\n");
	printf("%.5s\n", "oh mais non!");
	return (0);
}
