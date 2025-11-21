/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 00:23:41 by git               #+#    #+#             */
/*   Updated: 2025/11/21 00:23:41 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_hexlen(uintptr_t nb, int precision)
{
	int	len;

	len = 0;
	if (nb == 0 && precision == 0)
		return (0);
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

int	ft_intlen(uint64_t nb, int precision)
{
	int	len;

	len = 0;
	if (nb == 0 && precision == 0)
		return (0);
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

int	ft_hex_full_strlen(uintptr_t nb, int num_len, t_config *cfg, int is_ptr)
{
	int	tmp;
	int	str_len;

	str_len = num_len;
	if (cfg->precision > num_len)
		str_len = cfg->precision;
	if ((cfg->alt_form && nb != 0) || is_ptr)
		str_len += 2;
	if (is_ptr && cfg->force_sign)
		str_len++;
	if (cfg->width > str_len)
	{
		tmp = cfg->width;
		cfg->width = cfg->width - str_len;
		return (tmp);
	}
	else
		cfg->width = 0;
	return (str_len);
}

int	ft_int_full_strlen(int num_len, t_config *cfg)
{
	int	tmp;
	int	str_len;

	str_len = num_len;
	if (cfg->precision > num_len)
		str_len = cfg->precision;
	if (cfg->force_sign || cfg->is_neg || cfg->space_pad)
		str_len++;
	if (cfg->width > str_len)
	{
		tmp = cfg->width;
		cfg->width = cfg->width - str_len;
		return (tmp);
	}
	else
		cfg->width = 0;
	return (str_len);
}
