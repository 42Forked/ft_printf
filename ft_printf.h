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
	int				width;
	int				precision;
	int				zero_pad;
	int				space_pad;
	int				force_sign;
	int				left_justify;
	int				alt_form;
	int				is_neg;
	char			*str;
	int				i;
	long			l;
	unsigned int	ui;
	uintptr_t		ptr;
}					t_config;

typedef struct s_hexctx
{
	uintptr_t		nb;
	t_config		*cfg;
	int				num_len;
	int				str_len;
	int				i;
	char			pad_char;
	int				force_sign;
}					t_hexctx;

typedef struct s_intctx
{
	unsigned int	nb;
	t_config		*cfg;
	int				num_len;
	int				str_len;
	int				i;
	char			pad_char;
}					t_intctx;

int					ft_hex_full_strlen(int num_len, t_config *cfg, int is_ptr);
int					ft_hexlen(uintptr_t nb);
int					ft_int_full_strlen(int num_len, t_config *config);
int					ft_intlen(unsigned int nb, int precision);

char				*ft_gethex(uintptr_t nb, t_config *cfg, int is_upper,
						int is_ptr);

char				*ft_getint(unsigned int nb, t_config *cfg);

int					ft_printf(const char *format, ...);

#endif // FT_PRINTF_H
