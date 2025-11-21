/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: git <git@mart1d4.me>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:17:54 by git               #+#    #+#             */
/*   Updated: 2025/11/18 16:17:54 by git              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_config
{
	int			width;
	int			precision;
	int			zero_pad;
	int			space_pad;
	int			force_sign;
	int			left_justify;
	int			alt_form;
	int			is_neg;
	long		l;
}				t_config;

typedef struct s_hexctx
{
	uintptr_t	nb;
	t_config	*cfg;
	int			num_len;
	int			str_len;
	int			i;
	char		pad_char;
	int			force_sign;
}				t_hexctx;

typedef struct s_intctx
{
	uint64_t	nb;
	t_config	*cfg;
	int			num_len;
	int			str_len;
	int			i;
	char		pad_char;
}				t_intctx;

size_t			ft_strlen(const char *s);
int				ft_includes(const char *s, int c);

int				ft_parse_flags(t_config *config, int c);
int				ft_custom_atoi(t_config *cfg, int is_width, const char *s);
int				ft_parse_width_and_precision(t_config *config, const char *s,
					va_list va);

char			*ft_getchar(int c, t_config cfg);

char			*ft_getstr(const char *s, t_config cfg);

char			*ft_gethex(uintptr_t nb, t_config *cfg, int is_upper,
					int is_ptr);
int				ft_hexlen(uintptr_t nb, int precision);
int				ft_hex_full_strlen(uintptr_t nb, int num_len, t_config *cfg,
					int is_ptr);

char			*ft_getint(uint64_t nb, t_config *cfg);
int				ft_intlen(uint64_t nb, int precision);
int				ft_int_full_strlen(int num_len, t_config *config);

char			*ft_getptr(uintptr_t ptr, t_config *cfg);

int				ft_printf(const char *format, ...);

#endif // FT_PRINTF_H
