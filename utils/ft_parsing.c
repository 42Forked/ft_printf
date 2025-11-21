/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 04:34:26 by git               #+#    #+#             */
/*   Updated: 2025/11/20 04:58:14 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

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

int	ft_custom_atoi(t_config *cfg, int is_width, const char *s)
{
	int	res;
	int	i;

	if ((*s < '0' || *s > '9') && !is_width)
		cfg->precision = 0;
	if ((*s < '0' || *s > '9') && !is_width)
		return (0);
	if ((*s < '1' || *s > '9') && is_width)
	{
		if (*s == '0')
			cfg->width = 0;
		if (*s == 0)
			return (1);
		return (0);
	}
	i = 0;
	res = 0;
	while (s[i] >= '0' && s[i] <= '9')
		res = res * 10 + s[i++] - '0';
	if (is_width)
		cfg->width = res;
	else
		cfg->precision = res;
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
