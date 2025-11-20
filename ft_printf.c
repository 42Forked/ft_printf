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
#include "ft_printf.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int	ft_parse_flags(t_config *config, int c)
{
	if (c == ' ')
		config->space_pad = 1;
	if (c == '-')
		config->left_justify = 1;
	if (c == '+')
		config->force_sign = 1;
	if (c == '0')
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
	{
		config->precision = 0;
		return (0);
	}
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

int	ft_putchar_custom(int c, t_config config)
{
	int	i;

	i = 0;
	if (config.width > 0 && !config.left_justify)
	{
		while (i < config.width - 1)
		{
			write(1, " ", 1);
			i++;
		}
	}
	write(1, &c, 1);
	if (config.width > 0)
	{
		while (i < config.width - 1)
		{
			write(1, " ", 1);
			i++;
		}
	}
	return (i + 1);
}

int	ft_putstr_custom(const char *s, t_config config)
{
	int	i;
	int	str_len;

	i = 0;
	if (!s)
		str_len = 6;
	else
		str_len = ft_strlen(s);
	if (config.precision != -1 && config.precision < 6 && !s)
		str_len = 0;
	if (config.precision != -1 && config.precision < str_len)
		str_len = config.precision;
	while (!config.left_justify && i < config.width - str_len)
	{
		write(1, " ", 1);
		i++;
	}
	if (s && str_len > 0)
		write(1, s, str_len);
	else if (!s && str_len == 6)
		write(1, "(null)", 6);
	i += str_len;
	while (config.left_justify && i < config.width)
	{
		write(1, " ", 1);
		i++;
	}
	return (i);
}

int	ft_putptr_custom(uintptr_t ptr, t_config *cfg)
{
	int		len;
	char	*s;
	int		i;

	cfg->alt_form = 1;
	cfg->ui = 1;
	cfg->ptr = ptr;
	if (cfg->ptr == 0)
	{
		if (cfg->width <= 5)
		{
			write(1, "(nil)", 5);
			return (5);
		}
		s = (char *)malloc(sizeof(char) * (cfg->width - 4));
		if (!s)
			return (0);
		i = 0;
		while (i < cfg->width - 5)
			s[i++] = ' ';
		s[i] = '\0';
		if (cfg->left_justify)
			write(1, "(nil)", 5);
		write(1, s, cfg->width - 5);
		if (!cfg->left_justify)
			write(1, "(nil)", 5);
		free(s);
		return (cfg->width);
	}
	else
	{
		s = ft_gethex(ptr, cfg, 0, 1);
		len = ft_strlen(s);
		write(1, s, len);
		free(s);
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int				written;
	const char		*og_ptr;
	va_list			va;
	t_config		config;
	uint64_t		e;

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
		config = (t_config){.width = 0, .precision = -1, .alt_form = 0,
			.left_justify = 0, .zero_pad = 0, .force_sign = 0, .is_neg = 0};
		if (*format == '%')
			format++;
		while (*format != '\0' && ft_parse_flags(&config, *format))
			format++;
		format += ft_parse_width_and_precision(&config, format, va);
		if (ft_includes("cspdiuxX%", *format))
		{
			if (*format == 'c')
				written += ft_putchar_custom(va_arg(va, int), config);
			else if (*format == 's')
				written += ft_putstr_custom(va_arg(va, char *), config);
			else if (*format == 'p')
				written += ft_putptr_custom((uintptr_t)va_arg(va, void *),
						&config);
			else if (*format == 'd' || *format == 'i')
			{
				config.i = va_arg(va, int);
				if (config.i < 0)
				{
					e = (uint64_t)(-config.i);
					config.is_neg = 1;
				}
				else
				{
					e = (uint64_t)config.i;
				}
				config.str = ft_getint((unsigned int)e, &config);
				write(1, config.str, ft_strlen(config.str));
				written += ft_strlen(config.str);
				free(config.str);
			}
			else if (*format == 'x' || *format == 'X' || *format == 'u')
			{
				config.ui = va_arg(va, unsigned int);
				if (*format != 'u' && config.ui == 0 && config.precision == 0)
					write(1, "", 1);
				else
				{
					if (*format == 'u')
					{
						config.force_sign = 0;
						config.space_pad = 0;
						config.str = ft_getint(va_arg(va, unsigned int),
								&config);
					}
					else
						config.str = ft_gethex(config.ui, &config,
								*format == 'X', 0);
					write(1, config.str, ft_strlen(config.str));
					written += ft_strlen(config.str);
					free(config.str);
				}
			}
			else if (*format == '%')
				write(1, "%", 1);
			format++;
		}
		else
		{
			format++;
			write(1, og_ptr, format - og_ptr);
			written += format - og_ptr;
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

void	ft_test_unsigned(const char *s, unsigned int n)
{
	int	written_1;
	int	written_2;

	ft_printf("\n");
	ft_printf("ft_printf: [");
	written_1 = ft_printf(s, n);
	ft_printf("]\n");
	ft_printf("   printf: [");
	written_2 = printf(s, n);
	printf("]\n");
	printf("written_1: %d\nwritten_2:%d\n", written_1, written_2);
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

void	ft_test_pointers(const char *s, uintptr_t ptr)
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
	// ft_test_chars("%5c", 'E');
	// ft_test_chars("%-5c", 'E');
	// ft_test_chars("%05c", 'E');
	// ft_test_chars("%c", 'E');
	// ft_test_chars("%5c", 0);
	// ft_test_chars("%-5c", 0);
	// ft_test_chars("%c", 0);
	// ft_test_chars("%c", -56);
	// ft_test_chars("%c", 127);
	// ft_printf("\n| ------------- |   STRING    | -------------- |\n");
	// ft_test_strings("%s", "oh mais non!");
	// ft_test_strings("%.s", "salut mec");
	// ft_test_strings("%s", "hi");
	// ft_test_strings("%5s", "hi");
	// ft_test_strings("%-5s", "hi");
	// ft_test_strings("%.0s", "hi");
	// ft_test_strings("%.1s", "hi");
	// ft_test_strings("%.5s", "hi");
	// ft_test_strings("%.5s", "hi");
	// ft_test_strings("%5.1s", "hi");
	// ft_test_strings("%-5.1s", "hi");
	// ft_test_strings("%05s", "hi");
	// ft_test_strings("%0.4s", "hi");
	// ft_test_strings("%s", NULL);
	// ft_test_strings("%.3s", NULL);
	// ft_test_strings("%8.5s", NULL);
	// ft_test_strings("%-8s", NULL);
	// ft_test_strings("%s", "");
	// ft_test_strings("%5s", "");
	// ft_test_strings("%.0s", "");
	// ft_test_strings("%.100000s", "oh no!");
	// ft_test_strings("%.3s", "\xFF\xFE\xFD");
	// ft_printf("\n| ------------- |   POINTER   | -------------- |\n");
	// ft_test_pointers("%p", 7263);
	// ft_test_pointers("%4p", 72638374);
	// ft_test_pointers("%p", 0);
	// ft_test_pointers("%.3p", 0);
	// ft_test_pointers("%+-8.3p", 0);
	// ft_test_pointers("%-9.p", 0);
	// ft_test_pointers("%p", 1);
	// ft_test_pointers("%p", -1);
	// ft_test_pointers("%012.p", 383723);
	// ft_test_pointers("%012.2p", 383723);
	// ft_test_pointers("%#12p", 484723);
	// ft_test_pointers("% -37p", 0);
	// ft_test_pointers("%p", (uintptr_t)malloc(2627363));
	// ft_test_pointers("%-09p", (uintptr_t)malloc(283));
	// ft_test_pointers("%+#p", (uintptr_t)malloc(0));
	// ft_test_pointers("%+#12.4p", 37348);
	// ft_test_pointers("%+-#12.4p", 37348);
	ft_printf("\n| ------------- |     INT     | -------------- |\n");
	ft_test_ints("%05.4d", 42);
	ft_test_ints("%+d", -0);
	ft_test_ints("%.44d", 299);
	ft_test_ints("%.3d", 8393);
	ft_test_ints("%+.100d", -22);
	ft_test_ints("%+d", -372837);
	ft_test_ints("%d", 0);
	ft_test_ints("%d", 42);
	ft_test_ints("%d", -42);
	ft_test_ints("%5d", 42);
	ft_test_ints("%5d", -42);
	ft_test_ints("%-5d", 42);
	ft_test_ints("%-5d", -42);
	ft_test_ints("%+d", 42);
	ft_test_ints("% d", 42);
	ft_test_ints("%+d", -42);
	ft_test_ints("% d", -42);
	ft_test_ints("% +d", 42);
	ft_test_ints("%05d", 42);
	ft_test_ints("%05d", -42);
	ft_test_ints("%0+5d", 42);
	ft_test_ints("%0 5d", 42);
	ft_test_ints("%-05d", 42);
	ft_test_ints("%.0d", 0);
	ft_test_ints("%.1d", 0);
	ft_test_ints("%.3d", 42);
	ft_test_ints("%.3d", -42);
	ft_test_ints("%5.3d", 42);
	ft_test_ints("%5.3d", -42);
	ft_test_ints("%-5.3d", 42);
	ft_test_ints("%05.3d", 42);
	ft_test_ints("%2.5d", 42);
	ft_test_ints("%2d", -12345);
	ft_test_ints("%.0d", 1);
	ft_test_ints("%+.0d", 0);
	ft_test_ints("% .0d", 0);
	ft_test_ints("%+-5.3d", 42);
	ft_test_ints("% -5.3d", 42);
	ft_test_ints("%0+6.4d", -7);
	ft_test_ints("%d", INT_MAX);
	ft_test_ints("%+d", INT_MAX);
	ft_test_ints("%011d", INT_MAX);
	ft_test_ints("%d", INT_MIN);
	ft_test_ints("%+d", INT_MIN);
	ft_test_ints("%.11d", INT_MIN);
	ft_test_ints("%012d", INT_MIN);
	ft_test_ints("%0.0d", 0);
	ft_test_ints("%5.0d", 0);
	ft_test_ints("%-5.0d", 0);
	ft_test_ints("%+5.0d", 0);
	ft_test_ints("% 5.0d", 0);
	ft_test_ints("%i", -42);
	ft_test_ints("%+i", 42);
	ft_test_ints("% 5.0i", 0);
	ft_test_ints("%0+6i", 0);
	ft_test_ints("%.5d", -3);
	ft_test_ints("%6d", -3);
	ft_test_ints("%+6d", 0);
	ft_test_ints("% 6d", 0);
	ft_printf("\n| ------------- |  UNSIGNED  | ------------- |\n");
	ft_test_unsigned("%#8u", 18);
	ft_test_unsigned("%08u", 18);
	ft_test_unsigned("%08u", 18);
	ft_test_unsigned("%-02.3u", 18);
	ft_test_unsigned("%.00u", 28373482);
	ft_test_unsigned("%.00u", 38422);
	ft_test_unsigned("%u", 3872);
	ft_test_unsigned("%u", 9223372036854775807LL);
	ft_test_unsigned("%08u", 0);
	ft_test_unsigned("%08u", 1);
	ft_test_unsigned("%08u", -1);
	// ft_printf("\n| ------------- |     HEX     | ------------- |\n");
	// ft_test_hexs("%#8x", 18);
	// ft_test_hexs("%#08x", 18);
	// ft_test_hexs("%08x", 18);
	// ft_test_hexs("%-0#2.3x", 18);
	// ft_test_hexs("%.00x", 0);
	// ft_test_hexs("%#.00x", 0);
	// ft_test_hexs("%#x", 0);
	// ft_test_hexs("%#08x", 0);
	// ft_test_hexs("%.00x", 12);
	// ft_test_hexs("%9.x", 12);
	// ft_test_hexs("%.0x", 12);
	// ft_test_hexs("%#10X", 2748);
	// ft_test_hexs("%x", -1);
	// ft_test_hexs("%X", -1);
	// ft_test_hexs("%.8x", 12);
	// ft_test_hexs("%-#10x", 2748);
	// ft_test_hexs("%5x", 0);
	// ft_test_hexs("%#.5x", 0);
	// ft_test_hexs("%#8.5x", 0);
	// ft_test_hexs("%+x", 1);
	// ft_test_hexs("% x", 1);
	// ft_test_hexs("%3x", 11259375);
	// ft_test_hexs("%-#8.3x", 78);
	// ft_test_hexs("%+# 8.3x", 18);
	// ft_test_hexs("%# 012.5x", 18);
	// ft_test_hexs("%#- 012.2x", 18000);
	// ft_test_hexs("%#40.1x", 1883748);
	// ft_test_hexs("%# 012+.5xjehasbo%4x", 18);
	ft_printf("\n| ------------- |     END     | ------------- |\n");
	return (0);
}
