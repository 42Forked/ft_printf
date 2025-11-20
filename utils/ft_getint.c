/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 04:05:53 by git               #+#    #+#             */
/*   Updated: 2025/11/19 04:05:53 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>

static void	init_intctx(t_intctx *ctx, unsigned int nb, t_config *cfg)
{
	if (cfg->left_justify || (cfg->zero_pad && cfg->precision != -1))
		cfg->zero_pad = 0;
	ctx->nb = nb;
	ctx->cfg = cfg;
	ctx->num_len = ft_intlen(nb, cfg->precision);
	ctx->pad_char = '0';
	if (!cfg->zero_pad)
		ctx->pad_char = ' ';
	ctx->str_len = ft_int_full_strlen(ctx->num_len, cfg);
	ctx->i = 0;
}

static void	apply_left_padding_and_prefix(char *str, t_intctx *ctx)
{
	while (!ctx->cfg->left_justify && ctx->pad_char != '0'
		&& ctx->i < ctx->cfg->width)
	{
		str[ctx->i] = ctx->pad_char;
		ctx->i++;
	}
	if (ctx->cfg->force_sign && !ctx->cfg->is_neg)
		str[ctx->i++] = '+';
	else if (!ctx->cfg->force_sign && !ctx->cfg->is_neg && ctx->cfg->space_pad)
		str[ctx->i++] = ' ';
	else if (ctx->cfg->is_neg)
		str[ctx->i++] = '-';
}

static void	apply_zero_and_precision_padding(char *str, t_intctx *ctx)
{
	int	pad_i;

	pad_i = 0;
	while (ctx->pad_char == '0' && !ctx->cfg->left_justify
		&& pad_i < ctx->cfg->width)
	{
		str[ctx->i + pad_i] = ctx->pad_char;
		pad_i++;
	}
	ctx->i += pad_i;
	pad_i = 0;
	while (ctx->cfg->precision > ctx->num_len && pad_i < ctx->cfg->precision
		- ctx->num_len)
	{
		str[ctx->i + pad_i] = '0';
		pad_i++;
	}
	ctx->i += pad_i;
}

static void	apply_digits_and_right_padding(char *str, t_intctx *ctx)
{
	int	nb_i;

	nb_i = ctx->num_len - 1;
	if (ctx->cfg->is_neg)
		ctx->nb *= -1;
	while (nb_i >= 0)
	{
		str[ctx->i + nb_i] = "0123456789"[ctx->nb % 10];
		ctx->nb /= 10;
		nb_i--;
	}
	ctx->i += ctx->num_len;
	while (ctx->cfg->left_justify && ctx->i < ctx->str_len)
	{
		str[ctx->i] = ' ';
		ctx->i++;
	}
}

char	*ft_getint(unsigned int nb, t_config *cfg)
{
	t_intctx	ctx;
	char		*str;

	init_intctx(&ctx, nb, cfg);
	str = (char *)malloc(sizeof(char) * (ctx.str_len + 1));
	if (!str)
		return (NULL);
	apply_left_padding_and_prefix(str, &ctx);
	apply_zero_and_precision_padding(str, &ctx);
	apply_digits_and_right_padding(str, &ctx);
	str[ctx.str_len] = '\0';
	return (str);
}
