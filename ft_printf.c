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

#include "ft_printf.h"
//#include <limits.h>
//#include <stdint.h>
//#include <stdio.h>

static void	ft_write_str(char *s, int *written, int len)
{
	if (!s)
		return ;
	if (!len)
		len = ft_strlen(s);
	write(1, s, len);
	*written += len;
	free(s);
}

static void	ft_handle_specifier(char format, t_config cfg, int *written,
		va_list va)
{
	if (format == 'c' && cfg.width > 0)
		ft_write_str(ft_getchar(va_arg(va, int), cfg), written, cfg.width);
	if (format == 'c' && cfg.width <= 0)
		ft_write_str(ft_getchar(va_arg(va, int), cfg), written, 1);
	if (format == 's')
		ft_write_str(ft_getstr(va_arg(va, char *), cfg), written, 0);
	if (format == 'p')
		ft_write_str(ft_getptr((uintptr_t)va_arg(va, void *), &cfg), written,
			0);
	if (format == 'd' || format == 'i')
	{
		cfg.l = (long)va_arg(va, int);
		if (cfg.l < 0)
			cfg.is_neg = 1;
		if (cfg.l < 0)
			cfg.l = -cfg.l;
		ft_write_str(ft_getint((uintptr_t)cfg.l, &cfg), written, 0);
	}
	if (format == 'u')
		ft_write_str(ft_getint(va_arg(va, unsigned int), &cfg), written, 0);
	if (format == 'x' || format == 'X')
		ft_write_str(ft_gethex(va_arg(va, unsigned int), &cfg, format == 'X',
				0), written, 0);
	if (format == '%' && ++(*written))
		write(1, "%", 1);
}

static const char	*ft_parse_fmt(const char *format, va_list va, int *written)
{
	const char	*start;
	t_config	cfg;

	start = format;
	cfg = (t_config){.precision = -1};
	format++;
	while (*format && ft_parse_flags(&cfg, *format))
		format++;
	format += ft_parse_width_and_precision(&cfg, format, va);
	if (ft_includes("cspdiuxX%", *format))
	{
		ft_handle_specifier(*format, cfg, written, va);
		format++;
	}
	else
		write(1, start, format - start);
	return (format);
}

int	ft_printf(const char *format, ...)
{
	va_list		va;
	int			written;
	const char	*start;

	va_start(va, format);
	written = 0;
	while (*format)
	{
		start = format;
		while (*format && *format != '%')
			format++;
		write(1, start, format - start);
		written += (format - start);
		if (*format == '%')
			format = ft_parse_fmt(format, va, &written);
	}
	va_end(va);
	return (written);
}

//void	ft_test_chars(const char *s, char c)
//{
//	ft_printf("\n");
//	ft_printf("ft_printf: [");
//	ft_printf(s, c);
//	ft_printf("]\n");
//	ft_printf("   printf: [");
//	printf(s, c);
//	printf("]\n");
//}
//
//void	ft_test_strings(const char *s, char *str)
//{
//	ft_printf("\n");
//	ft_printf("ft_printf: [");
//	ft_printf(s, str);
//	ft_printf("]\n");
//	ft_printf("   printf: [");
//	printf(s, str);
//	printf("]\n");
//}
//
//void	ft_test_pointers(const char *s, intptr_t ptr)
//{
//	ft_printf("\n");
//	ft_printf("ft_printf: [");
//	ft_printf(s, ptr);
//	ft_printf("]\n");
//	ft_printf("   printf: [");
//	printf(s, ptr);
//	printf("]\n");
//}
//
//void	ft_test_ints(const char *s, int n)
//{
//	ft_printf("\n");
//	ft_printf("ft_printf: [");
//	ft_printf(s, n);
//	ft_printf("]\n");
//	ft_printf("   printf: [");
//	printf(s, n);
//	printf("]\n");
//}
//
//void	ft_test_unsigned(const char *s, unsigned int n)
//{
//	ft_printf("\n");
//	ft_printf("ft_printf: [");
//	ft_printf(s, n);
//	ft_printf("]\n");
//	ft_printf("   printf: [");
//	printf(s, n);
//	printf("]\n");
//}
//
//void	ft_test_hexs(const char *s, int n)
//{
//	ft_printf("\n");
//	ft_printf("ft_printf: [");
//	ft_printf(s, n);
//	ft_printf("]\n");
//	ft_printf("   printf: [");
//	printf(s, n);
//	printf("]\n");
//}
//
//int	main(void)
//{
//	ft_printf("| ------------- |    CHAR     | -------------- |\n");
//	ft_test_chars("%c", 'E');
//	ft_test_chars("%5c", 'E');
//	ft_test_chars("%-5c", 'E');
//	ft_test_chars("%05c", 'E');
//	ft_test_chars("%c", 'E');
//	ft_test_chars("%5c", 0);
//	ft_test_chars("%-5c", 0);
//	ft_test_chars("%c", 0);
//	ft_test_chars("%c", -56);
//	ft_test_chars("%c", 127);
//	ft_printf("\n| ------------- |   STRING    | -------------- |\n");
//	ft_test_strings("%s", "oh mais non!");
//	ft_test_strings("%.s", "salut mec");
//	ft_test_strings("%s", "hi");
//	ft_test_strings("%5s", "hi");
//	ft_test_strings("%-5s", "hi");
//	ft_test_strings("%.0s", "hi");
//	ft_test_strings("%.1s", "hi");
//	ft_test_strings("%.5s", "hi");
//	ft_test_strings("%.5s", "hi");
//	ft_test_strings("%5.1s", "hi");
//	ft_test_strings("%-5.1s", "hi");
//	ft_test_strings("%05s", "hi");
//	ft_test_strings("%0.4s", "hi");
//	ft_test_strings("%s", NULL);
//	ft_test_strings("%.3s", NULL);
//	ft_test_strings("%8.5s", NULL);
//	ft_test_strings("%-8s", NULL);
//	ft_test_strings("%s", "");
//	ft_test_strings("%5s", "");
//	ft_test_strings("%.0s", "");
//	ft_test_strings("%.100000s", "oh no!");
//	ft_test_strings("%.3s", "\xFF\xFE\xFD");
//	ft_printf("\n| ------------- |   POINTER   | -------------- |\n");
//	ft_test_pointers("%p", 7263);
//	ft_test_pointers("%4p", 72638374);
//	ft_test_pointers("%p", 0);
//	ft_test_pointers("%.3p", 0);
//	ft_test_pointers("%+-8.3p", 0);
//	ft_test_pointers("%-9.p", 0);
//	ft_test_pointers("%p", 1);
//	ft_test_pointers("%p", -1);
//	ft_test_pointers("%012.p", 383723);
//	ft_test_pointers("%012.2p", 383723);
//	ft_test_pointers("%#12p", 484723);
//	ft_test_pointers("% -37p", 0);
//	ft_test_pointers("%p", (uintptr_t)malloc(2627363));
//	ft_test_pointers("%-09p", (uintptr_t)malloc(283));
//	ft_test_pointers("%+#p", (uintptr_t)malloc(0));
//	ft_test_pointers("%+#12.4p", 37348);
//	ft_test_pointers("%+-#12.4p", 37348);
//	ft_printf("\n| ------------- |     INT     | -------------- |\n");
//	ft_test_ints("%05.4d", 42);
//	ft_test_ints("%+d", -0);
//	ft_test_ints("%.44d", 299);
//	ft_test_ints("%.3d", 8393);
//	ft_test_ints("%+.100d", -22);
//	ft_test_ints("%+d", -372837);
//	ft_test_ints("%d", 0);
//	ft_test_ints("%d", 42);
//	ft_test_ints("%d", -42);
//	ft_test_ints("%5d", 42);
//	ft_test_ints("%5d", -42);
//	ft_test_ints("%-5d", 42);
//	ft_test_ints("%-5d", -42);
//	ft_test_ints("%+d", 42);
//	ft_test_ints("% d", 42);
//	ft_test_ints("%+d", -42);
//	ft_test_ints("% d", -42);
//	ft_test_ints("% +d", 42);
//	ft_test_ints("%05d", 42);
//	ft_test_ints("%05d", -42);
//	ft_test_ints("%0+5d", 42);
//	ft_test_ints("%0 5d", 42);
//	ft_test_ints("%-05d", 42);
//	ft_test_ints("%.0d", 0);
//	ft_test_ints("%.1d", 0);
//	ft_test_ints("%.3d", 42);
//	ft_test_ints("%.3d", -42);
//	ft_test_ints("%5.3d", 42);
//	ft_test_ints("%5.3d", -42);
//	ft_test_ints("%-5.3d", 42);
//	ft_test_ints("%05.3d", 42);
//	ft_test_ints("%2.5d", 42);
//	ft_test_ints("%2d", -12345);
//	ft_test_ints("%.0d", 1);
//	ft_test_ints("%+.0d", 0);
//	ft_test_ints("% .0d", 0);
//	ft_test_ints("%+-5.3d", 42);
//	ft_test_ints("% -5.3d", 42);
//	ft_test_ints("%0+6.4d", -7);
//	ft_test_ints("%d", INT_MAX);
//	ft_test_ints("%+d", INT_MAX);
//	ft_test_ints("%011d", INT_MAX);
//	ft_test_ints("%d", INT_MIN);
//	ft_test_ints("%+d", INT_MIN);
//	ft_test_ints("%.11d", INT_MIN);
//	ft_test_ints("%012d", INT_MIN);
//	ft_test_ints("%0.0d", 0);
//	ft_test_ints("%5.0d", 0);
//	ft_test_ints("%-5.0d", 0);
//	ft_test_ints("%+5.0d", 0);
//	ft_test_ints("% 5.0d", 0);
//	ft_test_ints("%i", -42);
//	ft_test_ints("%+i", 42);
//	ft_test_ints("% 5.0i", 0);
//	ft_test_ints("%0+6i", 0);
//	ft_test_ints("%.5d", -3);
//	ft_test_ints("%6d", -3);
//	ft_test_ints("%+6d", 0);
//	ft_test_ints("% 6d", 0);
//	ft_printf("\n| ------------- |  UNSIGNED  | ------------- |\n");
//	ft_test_unsigned("%#8u", 18);
//	ft_test_unsigned("%08u", 42);
//	ft_test_unsigned("%u", 42);
//	ft_printf("%u", 42);
//	ft_test_unsigned("%08u", 18);
//	ft_test_unsigned("%-02.3u", 18);
//	ft_test_unsigned("%.00u", 28373482);
//	ft_test_unsigned("%.00u", 38422);
//	ft_test_unsigned("%u", 3872);
//	ft_test_unsigned("%u", 92775807);
//	ft_test_unsigned("%08u", 0);
//	ft_test_unsigned("%08u", 1);
//	ft_test_unsigned("%08u", -1);
//	ft_printf("\n| ------------- |     HEX     | ------------- |\n");
//	ft_test_hexs("%#8x", 18);
//	ft_test_hexs("%#08x", 18);
//	ft_test_hexs("%08x", 18);
//	ft_test_hexs("%-0#2.3x", 18);
//	ft_test_hexs("%.00x", 0);
//	ft_test_hexs("%#.00x", 0);
//	ft_test_hexs("%#x", 0);
//	ft_test_hexs("%#08x", 0);
//	ft_test_hexs("%.00x", 12);
//	ft_test_hexs("%9.x", 12);
//	ft_test_hexs("%.0x", 12);
//	ft_test_hexs("%#10X", 2748);
//	ft_test_hexs("%x", -1);
//	ft_test_hexs("%X", -1);
//	ft_test_hexs("%.8x", 12);
//	ft_test_hexs("%-#10x", 2748);
//	ft_test_hexs("%5x", 0);
//	ft_test_hexs("%#.5x", 0);
//	ft_test_hexs("%#8.5x", 0);
//	ft_test_hexs("%+x", 1);
//	ft_test_hexs("% x", 1);
//	ft_test_hexs("%3x", 11259375);
//	ft_test_hexs("%-#8.3x", 78);
//	ft_test_hexs("%+# 8.3x", 18);
//	ft_test_hexs("%# 012.5x", 18);
//	ft_test_hexs("%#- 012.2x", 18000);
//	ft_test_hexs("%#40.1x", 1883748);
//	ft_test_hexs("%42.5X", -1);
//	ft_test_hexs("%042x", 42000);
//	ft_test_hexs("%# 012+.5xjehasbo%4x", 18);
//	ft_printf("\n| ------------- |     END     | ------------- |\n");
//	return (0);
//}
