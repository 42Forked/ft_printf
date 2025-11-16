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

#include "../Libft/libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

int	ft_get_num_length_2(unsigned int nb, int base_len)
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

int	ft_get_str_len_2(int num_len, int full_len, int show_sign)
{
	int	str_len;

	str_len = num_len;
	if (full_len != -1 && full_len > num_len)
		str_len = full_len;
	if (show_sign)
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

char	*ft_get_padded_string_2(unsigned int nb, int num_len, int full_len,
		int show_sign)
{
	int		i;
	char	*str;
	int		str_len;

	str_len = ft_get_str_len_2(num_len, full_len, show_sign);
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (show_sign)
		*str = '+';
	if (show_sign)
		str++;
	while (full_len != -1 && i < full_len - num_len)
		str[i++] = '0';
	if (show_sign)
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

char	*ft_htoa_pad(unsigned int nb, int is_upper, int full_len)
{
	int		i;
	int		num_len;
	char	*str;

	num_len = ft_get_num_length_2(nb, 16);
	str = ft_get_padded_string_2(nb, num_len, full_len, 0);
	if (str == NULL)
		return (NULL);
	if (nb == 0)
		return (str);
	i = ft_get_str_len_2(num_len, full_len, 0);
	while (nb != 0)
	{
		if (is_upper)
			str[--i] = "0123456789ABCDEF"[nb % 16];
		else
			str[--i] = "0123456789abcdef"[nb % 16];
		nb /= 16;
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

static int	ft_includes(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

typedef struct s_settings
{
	int				width;
	int				precision;
	int				zero_pad;
	int				space_pad;
	int				show_sign;
	int				left_justify;
	int				alt_form;
	char			*str;
	int				i;
	unsigned int	ui;
	uintptr_t		ptr;
}					t_settings;

int	ft_parse_flags(t_settings *settings, int c)
{
	if (c == ' ')
		settings->space_pad = 1;
	if (c == '-')
		settings->left_justify = 1;
	if (c == '+')
		settings->show_sign = 1;
	if (c == '0')
		settings->zero_pad = 1;
	if (c == '#')
		settings->alt_form = 1;
	if (ft_includes(" -+0#", c))
		return (1);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int			written;
	const char	*og_ptr;
	va_list		va;
	t_settings	settings;

	written = 0;
	va_start(va, format);
	while (*format != '\0')
	{
		og_ptr = format;
		while (*format != '\0' && *format != '%')
			format++;
		write(1, og_ptr, format - og_ptr);
		written += format - og_ptr;
		settings = {-1};
		if (*format == '%')
			format++;
		while (*format != '\0' && ft_parse_flags(&settings, *format))
			format++;
		if (*format == '*')
		{
			settings.width = va_arg(va, int);
			format++;
		}
		else
		{
			settings.width = ft_atoi(format);
			while (ft_includes("0123456789", *format))
				format++;
		}
		if (*format == '.')
		{
			format++;
			if (*format == '*')
			{
				settings.width = va_arg(va, int);
				format++;
			}
			else
			{
				settings.width = ft_atoi(format);
				while (ft_includes("0123456789", *format))
					format++;
			}
		}
		if (ft_includes("cspdiuxX%", *format))
		{
			if (*format == 'c')
			{
				c = (char)va_arg(va, int);
				write(1, &c, 1);
			}
			else if (*format == 's')
			{
				str = va_arg(va, char *);
				write(1, str, ft_strlen(str));
			}
			else if (*format == 'p')
			{
				v = va_arg(va, void *);
				if (v == 0)
					write(1, "(nil)", 5);
				else
				{
					str = ft_htoa_pad((uintptr_t)v, 0, -1);
					write(1, "0x", 2);
					write(1, str, ft_strlen(str));
				}
			}
			else if (*format == 'd' || *format == 'i')
			{
				i = va_arg(va, int);
				str = ft_itoa_pad(i, -1, 0);
				write(1, str, ft_strlen(str));
			}
			else if (*format == 'x' || *format == 'X' || *format == 'u')
			{
				ui = va_arg(va, unsigned int);
				if (*format == 'u')
					str = ft_itoa_pad(ui, -1, 0);
				else
					str = ft_htoa_pad(ui, *format == 'X', -1);
				if (*format != 'u' && settings.show_hex_prefix && ui != 0)
				{
					if (*format == 'X')
						write(1, "0X", 2);
					else
						write(1, "0x", 2);
				}
				write(1, str, ft_strlen(str));
			}
			else if (*format == '%')
				write(1, "%", 1);
			format++;
		}
	}
	va_end(va);
	return (written);
}

void	ft_test_ints(const char *s, int n)
{
	ft_printf("\n");
	ft_printf("ft_printf: ");
	ft_printf(s, n);
	ft_printf("   printf: ");
	printf(s, n);
}

void	ft_test_hexs(const char *s, int n)
{
	ft_printf("\n");
	ft_printf("ft_printf: [");
	ft_printf(s, n);
	ft_printf("]\n");
	ft_printf("   printf: [");
	printf(s, n);
	printf("]\n");
}

void	ft_test_pointers(const char *s, void *ptr)
{
	ft_printf("\n");
	ft_printf("ft_printf: ");
	ft_printf(s, ptr);
	ft_printf("   printf: ");
	printf(s, ptr);
}

void	ft_test_strings(const char *s, char *str)
{
	ft_printf("\n");
	ft_printf("ft_printf: ");
	ft_printf(s, str);
	ft_printf("   printf: ");
	printf(s, str);
}

void	ft_test_chars(const char *s, char c)
{
	ft_printf("\n");
	ft_printf("ft_printf: ");
	ft_printf(s, c);
	ft_printf("   printf: ");
	printf(s, c);
}

int	main(void)
{
	ft_printf("| ------------- |    CHAR     | -------------- |\n");
	ft_test_chars("%c\n", 'E');
	ft_printf("\n| ------------- |   STRING    | -------------- |\n");
	ft_test_strings("%.5s\n", "oh mais non!");
	ft_printf("\n| ------------- |   POINTER   | -------------- |\n");
	ft_test_pointers("%p\n", (void *)7263);
	ft_test_pointers("%p\n", (void *)72638374);
	ft_test_pointers("%p\n", (void *)0);
	ft_printf("\n| ------------- |     INT     | -------------- |\n");
	ft_test_ints("%+d\n", -0);
	ft_test_ints("%.44d\n", 299);
	ft_test_ints("%.3d\n", 8393);
	ft_test_ints("%+.100d\n", -22);
	ft_test_ints("%+d\n", -372837);
	ft_printf("\n| ------------- |     HEX     | ------------- |\n");
	ft_test_hexs("%-13x]\n", 2221);
	ft_test_hexs("%013X]\n", 38374);
	ft_test_hexs("%#0.13X]\n", 38374);
	ft_test_hexs("%#13X]\n", 38374);
	ft_test_hexs("%X]\n", 892);
	ft_test_hexs("%#.X]\n", 181818);
	ft_test_hexs("%+#.x]\n", -2637);
	ft_test_hexs("%X]\n", -18983);
	ft_test_hexs("%X]\n", 27736);
	ft_test_hexs("%x]\n", -2);
	ft_test_hexs("%#x]\n", 0);
	ft_printf("\n| ------------- |     END     | ------------- |\n");
	return (0);
}
