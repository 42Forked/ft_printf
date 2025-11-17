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

int	ft_get_str_len(int nb, int num_len, int full_len, int force_sign)
{
	int	str_len;

	str_len = num_len;
	if (full_len != -1 && full_len > num_len)
		str_len = full_len;
	if (nb < 0 || force_sign)
		str_len++;
	return (str_len);
}

int	ft_get_str_len_2(int num_len, int full_len, int force_sign)
{
	int	str_len;

	str_len = num_len;
	if (full_len != -1 && full_len > num_len)
		str_len = full_len;
	if (force_sign)
		str_len++;
	return (str_len);
}

char	*ft_get_padded_string(int nb, int num_len, int full_len, int force_sign)
{
	int		i;
	char	*str;
	int		str_len;

	str_len = ft_get_str_len(nb, num_len, full_len, force_sign);
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (nb < 0)
		*str = '-';
	else if (force_sign)
		*str = '+';
	if (nb < 0 || force_sign)
		str++;
	while (full_len != -1 && i < full_len - num_len)
		str[i++] = '0';
	if (nb < 0 || force_sign)
		str--;
	if (nb == 0)
		str[str_len - 1] = '0';
	str[str_len] = '\0';
	return (str);
}

char	*ft_get_padded_string_2(unsigned int nb, int num_len, int full_len,
		int force_sign)
{
	int		i;
	char	*str;
	int		str_len;

	str_len = ft_get_str_len_2(num_len, full_len, force_sign);
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (force_sign)
		*str = '+';
	if (force_sign)
		str++;
	while (full_len != -1 && i < full_len - num_len)
		str[i++] = '0';
	if (force_sign)
		str--;
	if (nb == 0)
		str[str_len - 1] = '0';
	str[str_len] = '\0';
	return (str);
}

char	*ft_itoa_pad(int nb, int full_len, int force_sign)
{
	int		i;
	long	n;
	int		num_len;
	char	*str;

	num_len = ft_get_num_length(nb, 10);
	str = ft_get_padded_string(nb, num_len, full_len, force_sign);
	if (str == NULL)
		return (NULL);
	if (nb == 0)
		return (str);
	n = (long)nb;
	if (nb < 0)
		n *= -1;
	i = ft_get_str_len(nb, num_len, full_len, force_sign);
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

typedef struct s_config
{
	int				width;
	int				precision;
	int				zero_pad;
	int				space_pad;
	int				force_sign;
	int				left_justify;
	int				alt_form;
	char			*str;
	int				i;
	unsigned int	ui;
	uintptr_t		ptr;
}					t_config;

int	ft_parse_flags(t_config *config, int c)
{
	if (c == ' ' && !config->force_sign)
		config->space_pad = 1;
	if (c == '-')
	{
		config->left_justify = 1;
		config->zero_pad = 0;
	}
	if (c == '+')
	{
		config->force_sign = 1;
		config->space_pad = 0;
	}
	if (c == '0' && !config->precision && !config->left_justify)
		config->zero_pad = 1;
	if (c == '#')
		config->alt_form = 1;
	if (ft_includes(" -+0#", c))
		return (1);
	return (0);
}

int	ft_custom_atoi(t_config *config, int is_width, const char *s)
{
	int	res;
	int	i;

	if ((*s < '0' || *s > '9') && !is_width)
		return (0);
	if ((*s < '1' || *s > '9') && is_width)
	{
		if (is_width && *s == '0')
			config->width = 0;
		else if (!is_width && *s == '0')
			config->precision = 0;
		if (*s == 0)
			return (1);
		return (0);
	}
	i = 0;
	res = 0;
	while (s[i] >= '0' && s[i] <= '9')
		res = res * 10 + s[i++] - '0';
	if (is_width)
		config->width = res;
	else
		config->precision = res;
	return (i);
}

int	ft_parse_width_and_precision(t_config *config, const char *s, va_list va)
{
	const char	*og_ptr;

	og_ptr = s;
	if (*s == '*')
	{
		config->width = va_arg(va, int);
		s++;
	}
	else
		s += ft_custom_atoi(config, 1, s);
	if (*s == '.')
	{
		s++;
		config->width = -1;
		if (*s == '*')
		{
			config->precision = va_arg(va, int);
			s++;
		}
		else
			s += ft_custom_atoi(config, 0, s);
	}
	return (s - og_ptr);
}

int	ft_printf(const char *format, ...)
{
	int			written;
	const char	*og_ptr;
	va_list		va;
	t_config	config;

	written = 0;
	va_start(va, format);
	while (*format != '\0')
	{
		og_ptr = format;
		while (*format != '\0' && *format != '%')
			format++;
		write(1, og_ptr, format - og_ptr);
		written += format - og_ptr;
		if (*format == '\0')
			return (written);
		config = (t_config){.width = -1, .precision = -1};
		if (*format == '%')
			format++;
		while (*format != '\0' && ft_parse_flags(&config, *format))
			format++;
		format += ft_parse_width_and_precision(&config, format, va);
		if (ft_includes("cspdiuxX%", *format))
		{
			if (*format == 'c')
			{
				config.i = va_arg(va, int);
				write(1, &config.i, 1);
			}
			else if (*format == 's')
			{
				config.str = va_arg(va, char *);
				write(1, config.str, ft_strlen(config.str));
			}
			else if (*format == 'p')
			{
				config.ptr = (uintptr_t)va_arg(va, void *);
				if (config.ptr == 0)
					write(1, "(nil)", 5);
				else
				{
					config.str = ft_htoa_pad((uintptr_t)config.ptr, 0, -1);
					write(1, "0x", 2);
					write(1, config.str, ft_strlen(config.str));
				}
			}
			else if (*format == 'd' || *format == 'i')
			{
				config.i = va_arg(va, int);
				config.str = ft_itoa_pad(config.i, config.precision,
						config.force_sign);
				write(1, config.str, ft_strlen(config.str));
			}
			else if (*format == 'x' || *format == 'X' || *format == 'u')
			{
				config.ui = va_arg(va, unsigned int);
				if (*format != 'u' && config.alt_form && config.ui != 0)
				{
					config.width = config.width - 2;
					if (*format == 'X')
						write(1, "0X", 2);
					else
						write(1, "0x", 2);
				}
				if (*format == 'u')
					config.str = ft_itoa_pad(config.ui, config.width,
							config.force_sign);
				else
					config.str = ft_htoa_pad(config.ui, *format == 'X',
							config.width);
				if (*format != 'u' && config.ui == 0 && config.precision == 0)
					write(1, "", 1);
				else
					write(1, config.str, ft_strlen(config.str));
			}
			else if (*format == '%')
				write(1, "%", 1);
			format++;
		}
		else
		{
			write(1, og_ptr, format + 1 - og_ptr);
			written += format + 1 - og_ptr;
		}
	}
	va_end(va);
	return (written);
}

void	ft_test_ints(const char *s, int n)
{
	ft_printf("\n");
	ft_printf("ft_printf: [");
	ft_printf(s, n);
	ft_printf("]\n");
	ft_printf("   printf: [");
	printf(s, n);
	printf("]\n");
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
	ft_printf("ft_printf: [");
	ft_printf(s, ptr);
	ft_printf("]\n");
	ft_printf("   printf: [");
	printf(s, ptr);
	printf("]\n");
}

void	ft_test_strings(const char *s, char *str)
{
	ft_printf("\n");
	ft_printf("ft_printf: [");
	ft_printf(s, str);
	ft_printf("]\n");
	ft_printf("   printf: [");
	printf(s, str);
	printf("]\n");
}

void	ft_test_chars(const char *s, char c)
{
	ft_printf("\n");
	ft_printf("ft_printf: [");
	ft_printf(s, c);
	ft_printf("]\n");
	ft_printf("   printf: [");
	printf(s, c);
	printf("]\n");
}

int	main(void)
{
	// ft_printf("| ------------- |    CHAR     | -------------- |\n");
	// ft_test_chars("%c", 'E');
	// ft_printf("\n| ------------- |   STRING    | -------------- |\n");
	// ft_test_strings("%.5s", "oh mais non!");
	// ft_printf("\n| ------------- |   POINTER   | -------------- |\n");
	// ft_test_pointers("%p", (void *)7263);
	// ft_test_pointers("%p", (void *)72638374);
	// ft_test_pointers("%p", (void *)0);
	// ft_printf("\n| ------------- |     INT     | -------------- |\n");
	// ft_test_ints("%+d%+d%+d%+d%+d%+d%+d", -0);
	// printf("\n%+d%+d%+.22d%+d%+d%+d%+d\n", -0, 0, 0, -55, 0, -0, 0);
	// ft_printf("\n%+d%+d%+.22d%+d%+d%+d%+d\n", -0, 0, 0, -55, 0, -0, 0);
	// ft_test_ints("%.44d", 299);
	// ft_test_ints("%.3d", 8393);
	// ft_test_ints("%+.100d", -22);
	// ft_test_ints("%+d", -372837);
	// ft_printf("\n| ------------- |     HEX     | ------------- |\n");
	// ft_test_hexs("%#8x", 18);
	// ft_test_hexs("%#08x", 18);
	// ft_test_hexs("%08x", 18);
	// ft_test_hexs("%8.3x", 18);
	ft_test_hexs("%.00x", 0);
	ft_test_hexs("%#.00x", 0);
	ft_test_hexs("%.00x", 12);
	// ft_test_hexs("%#10X", 2748);
	// ft_test_hexs("%x", -1);
	// ft_test_hexs("%X", -1);
	// ft_test_hexs("%.8x", 12);
	// ft_test_hexs("%-#10x", 2748);
	// ft_test_hexs("%5x", 0);
	// ft_test_hexs("%#.5x", 0);
	// ft_test_hexs("%+x", 1);
	// ft_test_hexs("% x", 1);
	// ft_test_hexs("%3x", 11259375);
	// ft_printf("\n| ------------- |     END     | ------------- |\n");
	return (0);
}
