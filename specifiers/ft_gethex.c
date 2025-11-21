/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:06:57 by git               #+#    #+#             */
/*   Updated: 2025/11/18 17:06:57 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	init_hexctx(t_hexctx *ctx, uintptr_t nb, t_config *cfg, int is_ptr)
{
	if (cfg->precision != -1)
		cfg->zero_pad = 0;
	ctx->nb = nb;
	ctx->cfg = cfg;
	ctx->num_len = ft_hexlen(nb, cfg->precision);
	ctx->pad_char = '0';
	if ((!cfg->zero_pad && cfg->precision <= 0) || cfg->left_justify
		|| (cfg->alt_form && cfg->precision != -1))
		ctx->pad_char = ' ';
	ctx->str_len = ft_hex_full_strlen(nb, ctx->num_len, cfg, is_ptr);
	ctx->force_sign = is_ptr && cfg->force_sign;
	ctx->i = 0;
}

static void	apply_left_padding_and_prefix(char *str, t_hexctx *ctx,
		int is_upper)
{
	while ((ctx->pad_char == ' ' || !ctx->cfg->alt_form)
		&& !ctx->cfg->left_justify && ctx->i < ctx->cfg->width)
	{
		if (ctx->cfg->zero_pad)
			str[ctx->i] = '0';
		else
			str[ctx->i] = ' ';
		ctx->i++;
	}
	if (ctx->force_sign)
		str[ctx->i++] = '+';
	if (ctx->cfg->alt_form && ctx->nb != 0)
	{
		str[ctx->i++] = '0';
		str[ctx->i++] = "xX"[is_upper];
	}
}

static void	apply_zero_and_precision_padding(char *str, t_hexctx *ctx)
{
	int	pad_i;

	pad_i = 0;
	while (ctx->pad_char == '0' && ctx->cfg->alt_form && !ctx->cfg->left_justify
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

static void	apply_digits_and_right_padding(char *str, t_hexctx *ctx,
		int is_upper)
{
	int		nb_i;
	char	*base;

	if (is_upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	nb_i = ctx->num_len - 1;
	while (nb_i >= 0 && (ctx->nb > 0 || ctx->cfg->precision != 0))
	{
		str[ctx->i + nb_i] = base[ctx->nb % 16];
		ctx->nb /= 16;
		nb_i--;
	}
	ctx->i += ctx->num_len;
	while (ctx->cfg->left_justify && ctx->i < ctx->str_len)
	{
		str[ctx->i] = ctx->pad_char;
		ctx->i++;
	}
}

char	*ft_gethex(uintptr_t nb, t_config *cfg, int is_upper, int is_ptr)
{
	t_hexctx	ctx;
	char		*str;

	init_hexctx(&ctx, nb, cfg, is_ptr);
	str = (char *)malloc(sizeof(char) * (ctx.str_len + 1));
	if (!str)
		return (NULL);
	apply_left_padding_and_prefix(str, &ctx, is_upper);
	apply_zero_and_precision_padding(str, &ctx);
	apply_digits_and_right_padding(str, &ctx, is_upper);
	str[ctx.str_len] = '\0';
	return (str);
}
